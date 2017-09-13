#pragma once
#include "src_headers.h"
#include <cstdio>

bool __fastcall hkCreateMove(void *current_hook, void *s, float f, CUserCmd *cmd)
{
    if (cmd->command_number == 0) //if command_number is 0 then ExtraMouseSample is being called
        return 0;

    static int x = 5;
    printf("ayy %d\n", x++);

    return 0;
}