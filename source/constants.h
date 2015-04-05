#pragma once

#include <3ds.h>

extern u32 kmem_start; 
extern u32 kproc_start;
extern u32 kproc_size;
extern u32 kproc_num;
extern u32 kproc_codeset_offset;

bool GetVersionConstants();