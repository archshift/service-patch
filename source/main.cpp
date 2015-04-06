#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <3ds.h>

#include "constants.h"
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
    // svcBackdoor(PatchProcessWrapper);
    // log("[0x%08X] - Patched process\n", ret);

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
