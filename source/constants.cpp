#include "constants.h"

u32 kmem_start  = 0; 
u32 kproc_start = 0;
u32 kproc_size  = 0;
u32 kproc_num   = 0;
u32 kproc_codeset_offset = 0;

bool GetVersionConstants()
{
    u32 kversion = *(vu32*)0x1FF80000; // KERNEL_VERSION register

    u8 is_n3ds = 0;
    APT_CheckNew3DS(NULL, &is_n3ds);

    if (!is_n3ds || kversion < 0x022C0600) {
        switch (kversion) {
            case 0x02220000: // 2.34-0 4.1.0
                kproc_size  = 0x260;
                kproc_codeset_offset = 0xA8;
                break;
            case 0x02230600: // 2.35-6 5.0.0
                kproc_size  = 0x260;
                kproc_codeset_offset = 0xA8;
                break;
            case 0x02240000: // 2.36-0 5.1.0
                kproc_size  = 0x260;
                kproc_codeset_offset = 0xA8;
                break;
            case 0x02250000: // 2.37-0 6.0.0
                kproc_size  = 0x260;
                kproc_codeset_offset = 0xA8;
                break;
            case 0x02260000: // 2.38-0 6.1.0
                kproc_size  = 0x260;
                kproc_codeset_offset = 0xA8;
                break;
            case 0x02270400: // 2.39-4 7.0.0
                kproc_size  = 0x260;
                kproc_codeset_offset = 0xA8;
                break;
            case 0x02280000: // 2.40-0 7.2.0
                kproc_size  = 0x260;
                kproc_codeset_offset = 0xA8;
                break;
            case 0x022C0600: // 2.44-6 8.0.0
                kproc_size  = 0x268;
                kproc_num   = 0x2C;
                kproc_codeset_offset = 0xB0;
                break;
            case 0x022E0000: // 2.26-0 9.0.0
                kmem_start  = 0xDFF80000;
                kproc_start = kmem_start + 0x25730;
                kproc_size  = 0x268;
                kproc_num   = 0x2C;
                kproc_codeset_offset = 0xB0;
                return true;
        }
    } else {
        switch (kversion) {
            case 0x022C0600: // N3DS 2.44-6 8.0.0
                kproc_size = 0x270;
                kproc_num = 0x2F;
                kproc_codeset_offset = 0xB8;
                break;
            case 0x022E0000: // N3DS 2.26-0 9.0.0
                kproc_size = 0x270;
                kproc_num = 0x2F;
                kproc_codeset_offset = 0xB8;
                break;
        }
    }

    return false;
}