#pragma once

#include <3ds.h>

extern "C" {
	extern int ret;

    s32 PatchPid();
    s32 UnpatchPid();

    int PatchProcess();
    s32 PatchProcessWrapper();
}

void ReinitSrv();
void PatchSrvAccess();

