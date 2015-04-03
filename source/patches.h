#pragma once

#include <3ds.h>

extern "C" {
	extern int ret;

    s32 patch_pid();
    s32 unpatch_pid();

    int patch_process();
    s32 patch_process_wrapper();
}

void reinit_srv();
void patch_srv_access();

