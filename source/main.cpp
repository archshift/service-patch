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
    consoleInit(GFX_TOP, NULL);

    if (!GetVersionConstants()) {
        log("Warning, your platform is (either fully or partially) unsupported!\n");
    }
    

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

    gfxExit();
    return 0;
}
