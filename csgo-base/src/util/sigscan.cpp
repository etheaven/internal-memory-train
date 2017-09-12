#include "../constants/definitions.h"
#include "sigscan.h"
ulong util::findpattern(ulong addr, int len, const char *p)
{
    for (int i = 0; i < len; ++addr)
    {
        if (util::cmp((const char *)addr, p))
            return addr;
    }
    return 0;
}

int util::cmp(const char *addr, const char *p)
{
    for (; *p; ++addr, ++p)
    {
        if (*p != '?' && *addr != *p)
            return 0;
    }
    return (*p == 0);
}