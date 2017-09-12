#pragma once
#include "src_headers.h"
#include <cstdio>

void hkCreateMove(void *thisptr, void *s, float f, CUserCmd *cmd)
{
    static CreateMove_t oCreateMove = vmt_cmove->GetOriginalFunction<CreateMove_t>(24);
    // Call original 'IBaseClientDLL::CreateMove'.
    oCreateMove(thisptr, s, f, cmd);
    static int x = 5;
    printf("ayy %d\n", x++);
}