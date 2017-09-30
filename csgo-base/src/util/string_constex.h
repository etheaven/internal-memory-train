#pragma once
#include <array>
#include <iostream>
#include <string>

typedef uint32_t u32;
typedef uint64_t u64;
typedef unsigned char uchar;

template<u32 S, u32 A = 16807UL, u32 C = 0UL, u32 M = (1UL<<31)-1>
struct LinearGenerator {
    static const u32 state = ((u64)S * A + C) % M;
    static const u32 value = state;
    typedef LinearGenerator<state> next;
    struct Split { // Leapfrog
        typedef LinearGenerator< state, A*A, 0, M> Gen1;
        typedef LinearGenerator<next::state, A*A, 0, M> Gen2;
    };
};

// Metafunction to get a particular index from generator
template<u32 S, std::size_t index>
struct Generate {
    static const uchar value = Generate<LinearGenerator<S>::state, index - 1>::value;
};

template<u32 S>
struct Generate<S, 0> {
    static const uchar value = static_cast<uchar> (LinearGenerator<S>::value);
};

// List of indices
template<std::size_t...>
struct StList {};

// Concatenate
template<typename TL, typename TR>
struct Concat;

template<std::size_t... SL, std::size_t... SR>
struct Concat<StList<SL...>, StList<SR...>> {
    typedef StList<SL..., SR...> type;
};

template<typename TL, typename TR>
using Concat_t = typename Concat<TL, TR>::type;

// Count from zero to n-1
template<size_t s>
struct Count {
    typedef Concat_t<typename Count<s-1>::type, StList<s-1>> type;
};

template<>
struct Count<0> {
    typedef StList<> type;
};

template<size_t s>
using Count_t = typename Count<s>::type;

// Get a scrambled character of a string
template<u32 seed, std::size_t index, std::size_t N>
constexpr uchar get_scrambled_char(const char(&a)[N]) {
    return static_cast<uchar>(a[index]) + Generate<seed, index>::value;
}

// Get a ciphertext from a plaintext string
template<u32 seed, typename T>
struct cipher_helper;

template<u32 seed, std::size_t... SL>
struct cipher_helper<seed, StList<SL...>> {
    static constexpr std::array<uchar, sizeof...(SL)> get_array(const char (&a)[sizeof...(SL)]) {
        return {{ get_scrambled_char<seed, SL>(a)... }};
    }
};

template<u32 seed, std::size_t N>
constexpr std::array<uchar, N> get_cipher_text (const char (&a)[N]) {
    return cipher_helper<seed, Count_t<N>>::get_array(a);
}

// Get a noise sequence from a seed and string length
template<u32 seed, typename T>
struct noise_helper;

template<u32 seed, std::size_t... SL>
struct noise_helper<seed, StList<SL...>> {
    static constexpr std::array<uchar, sizeof...(SL)> get_array() {
        return {{ Generate<seed, SL>::value ... }};
    }
};

template<u32 seed, std::size_t N>
constexpr std::array<uchar, N> get_key() {
    return noise_helper<seed, Count_t<N>>::get_array();
}

// Metafunction to get the size of an array
template<typename T>
struct array_info;

template <typename T, size_t N>
struct array_info<T[N]>
{
    typedef T type;
    enum { size = N };
};

template <typename T, size_t N>
struct array_info<const T(&)[N]> : array_info<T[N]> {};

// Scramble a string
template<u32 seed, std::size_t N>
class obfuscated_string {
private:
    std::array<uchar, N> cipher_text_;
    std::array<uchar, N> key_;
public:
    explicit constexpr obfuscated_string(const char(&a)[N])
        : cipher_text_(get_cipher_text<seed, N>(a))
        , key_(get_key<seed,N>())
    {}

    operator std::string() const {
        char plain_text[N];
        for (volatile std::size_t i = 0; i < N; ++i) {
            volatile char temp = static_cast<char>( cipher_text_[i] - key_[i] );
            plain_text[i] = temp;
        }
        return std::string{plain_text, plain_text + N};
    }
};

template<u32 seed, std::size_t N>
std::ostream & operator<< (std::ostream & s, const obfuscated_string<seed, N> & str) {
    s << static_cast<std::string>(str);
    return s;
}

#define RNG_SEED ((__TIME__[7] - '0') * 16  + (__TIME__[6] - '0') * 18  + \
              (__TIME__[4] - '0') * 56   + (__TIME__[3] - '0') * 6666 + \
              (__TIME__[1] - '0') * 9156 + (__TIME__[0] - '0') * 96122) + \
              (__LINE__ * 641529)


#define LIT(STR) \
    obfuscated_string<RNG_SEED, array_info<decltype(STR)>::size>{STR}