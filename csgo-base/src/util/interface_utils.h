#pragma once
#include <Windows.h>
namespace util
{
typedef void *(*InstantiateInterface)();

class CInterface
{
  public:
    InstantiateInterface Interface; //0x0000
    char *InterfaceName;            //0x0004
    CInterface *NextInterface;      //0x0008

}; //Size=0x000C

void *EasyInterface(const char *_Module, const char *_Object)
{
    /*
       1E6EC9D0 | 55                       | push ebp                                |
       1E6EC9D1 | 8B EC                    | mov ebp,esp                             |
       1E6EC9D3 | 56                       | push esi                                |
       1E6EC9D4 | 8B 35 B0 41 97 1E        | mov esi,dword ptr ds:[1E9741B0]         |
       
       1E6ECD20 | 55                       | push ebp                                |
       1E6ECD21 | 8B EC                    | mov ebp,esp                             |
       1E6ECD23 | 5D                       | pop ebp                                 |
       1E6ECD24 | E9 A7 FC FF FF           | jmp client.1E6EC9D0                     |
       */

    ULONG CreateInterface = (ULONG)GetProcAddress(GetModuleHandle(_Module), "CreateInterface");

    ULONG ShortJump = (ULONG)CreateInterface + 5; //magic number shit explained above

    ULONG Jump = (((ULONG)CreateInterface + 5) + *(ULONG *)ShortJump) + 4;

    CInterface *List = **(CInterface ***)(Jump + 6);

    do
    {
        if (List)
        {
            if (strstr(List->InterfaceName, _Object) && (strlen(List->InterfaceName) - strlen(_Object)) < 5 /*arbitrary number to see that both names aren't too different*/)
                return List->Interface();
        }

    } while (List = List->NextInterface);

    return 0;
}
}