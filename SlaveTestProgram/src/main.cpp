#include <Windows.h>
#include <iostream>

double function(double arg)
{
    std::cout << "Function: Much easier to find me this way! " << arg << std::endl;
    return arg;
}

void function2()
{
    std::cout << "Function2: This is function2." << std::endl;
}

int main()
{
    std::cout << "My start: " << std::hex << (void *)function << "\n";
    while(true)
    {
        Sleep(2500);
        function(3.14);
        Sleep(2500);
        function2();
    }

    return 0;
}