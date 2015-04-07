#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <3ds.h>

#include "constants.h"
#include "kernel11.h"
#include "patches.h"

#define log(...) fprintf(stderr, __VA_ARGS__)

int main(int argc, char** argv)
{
    gfxInitDefault();
    hbInit();
    consoleInit(GFX_TOP, NULL);

    SaveVersionConstants();
    PatchSrvAccess();

// ONLY UNCOMMENT AFTER CUSTOMIZING PatchProcessWrapper
    // log("[%08X] Patched process\n", KernelBackdoor(PatchProcess));
    // HB_FlushInvalidateCache(); // Just to be sure!

    // Main loop
    while (aptMainLoop())
    {
        hidScanInput();

        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
            break;
        gspWaitForVBlank();
    }

    hbExit();
    gfxExit();
    return 0;
}
