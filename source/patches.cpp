#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <3ds.h>

#include "patches.h"
#include "kobjects.h"

//-----------------------------------------------------------------------------

u32 self_pid = 0;

void ReinitSrv()
{
    srvExit();
    srvInit();
}

void PatchSrvAccess()
{
    svcGetProcessId(&self_pid, 0xFFFF8001);
    printf("Current process id: %lu\n", self_pid);

    printf("Patching srv access...");
    svcBackdoor(PatchPid);
    ReinitSrv();

    u32 new_pid;
    svcGetProcessId(&new_pid, 0xFFFF8001);
    printf("%s\n", new_pid == 0 ? "succeeded!" : "failed!");

    // Cleanup; won't take effect until srv is reinitialized
    svcBackdoor(UnpatchPid);
}

//-----------------------------------------------------------------------------

int PatchProcess()
{
    // Target title id
    static const u64 title_id = 0;

    // Offset of patch location from process base memory address
    static const u32 patch_offset = 0;

    // Assembled opcode (big endian)
    // Example: nop (0xE1A00000)
    static const u64 patch_code = 0;

    KCodeSet* code_set = FindTitleCodeSet(title_id);
    if (code_set == nullptr)
        return 1;
    
    *(u32*)FindCodeOffsetKAddr(code_set, patch_offset) = patch_code;
    return 0;
}