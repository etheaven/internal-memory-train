#include <iostream>
#include <Windows.h>
typedef double(__cdecl *my_function)(double);
using ulong = unsigned long;

void call_once(ulong addr, double value)
{
  my_function f = (my_function)addr;
  f(value);
}

bool Redirect(void *Dst, void *Src, int size)
{
  if (size < 5)
    return false;
  static const byte asm_ret = 0xC3;
  ulong old_protec = PAGE_EXECUTE_READ;                           // just in case
  VirtualProtect(Dst, size, PAGE_EXECUTE_READWRITE, &old_protec); // now I can read and write at address of Dst for size bytes
  memset(Dst, asm_ret, size);                                     // prevent undefined behaviour
  ulong relative_addr = 0;
  if (Dst < Src)
    relative_addr += ((ulong)Src - (ulong)Dst) - 5;
  else
    relative_addr += ((ulong)Src - (ulong)Dst) + 5;
  *(byte *)Dst = 0xE9;                        // make it JMP
  *(ulong *)((ulong)Dst + 1) = relative_addr; // where I jump to
  ulong tmp;
  VirtualProtect(Src, size, old_protec, &tmp); // change it back
  return true;
}

ulong jmpBackAddr = 0;
void Replace(void *Dst, void *Src, int size)
{
  ulong hkAddr = (ulong)Dst;
  jmpBackAddr = hkAddr + size;
  Redirect(Dst, Src, size);
}

double hkFn(double x)
{
  std::cout << "it was " << x << "\n";               // written
  x += 1334.55;                                      // computed
  my_function originalFn = (my_function)jmpBackAddr; // completely ignored as if it were non-existant
  return originalFn(x);
}

extern "C" BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved)
{
  switch (ul_reason_for_call)
  {
  case DLL_PROCESS_ATTACH:
    call_once(0x401500, 432.10);
    Replace((void *)0x401500, (void *)hkFn, 6); // works on MSVC, doesn't on g++ (does nothing at all with originalFn)
    call_once(0x401500, 432.10);
    // now this is interesting, this commented line crashes MSVC but works completely fine on g++
    //call_once(0x401500, 432.10);
    break;
  }
  return TRUE;
}