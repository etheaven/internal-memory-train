#pragma once
#include <Windows.h>

class VMTManager
{
  private:
    DWORD *OriginalTable;
    DWORD *CustomTable;
    int MethodCount(DWORD *InstancePointer)
    {
        DWORD *VMT = (DWORD *)*InstancePointer;
        int Index = 0;
        int Amount = 0;
        while (!IsBadCodePtr((FARPROC)VMT[Index]))
        {
            if (!IsBadCodePtr((FARPROC)VMT[Index]))
            {
                Amount++;
                Index++;
            }
        }

        return Amount;
    }
    bool initComplete;
    DWORD *Instance;

  public:
    bool Initialise(DWORD *InstancePointer)
    {
        // Store the instance pointers and such, and work out how big the table is
        Instance = InstancePointer;
        OriginalTable = (DWORD *)*InstancePointer;
        int VMTSize = MethodCount(InstancePointer);
        size_t TableBytes = VMTSize * 4;

        // Allocate some memory and copy the table
        CustomTable = (DWORD *)malloc(TableBytes + 8);
        if (!CustomTable)
            return false;
        memcpy((void *)CustomTable, (void *)OriginalTable, VMTSize * 4);

        // Change the pointer
        *InstancePointer = (DWORD)CustomTable;

        initComplete = true;
        return true;
    }

    DWORD HookMethod(DWORD NewFunction, int Index)
    {
        if (initComplete)
        {
            CustomTable[Index] = NewFunction;
            return OriginalTable[Index];
        }
        else
            return NULL;
    }
    void UnhookMethod(int Index)
    {
        if (initComplete)
            CustomTable[Index] = OriginalTable[Index];
        return;
    }

    static bool IsTableHooked(DWORD *InstancePointer);

    void RestoreOriginal()
    {
        if (initComplete)
        {
            *Instance = (DWORD)OriginalTable;
        }
        return;
    }
    void RestoreCustom()
    {
        if (initComplete)
        {
            *Instance = (DWORD)CustomTable;
        }
        return;
    }

    DWORD GetOriginalFunction(int Index)
    {
        return OriginalTable[Index];
    }
};