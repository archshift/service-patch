#include "kobjects.h"

static const u32 KMEM_START  = 0xDFF80000; 
static const u32 KPROC_START = KMEM_START + 0x25730;
static const u32 KPROC_SIZE  = 0x268;
static const u32 KPROC_NUM   = 0x2C;
static const u32 PAGE_SIZE   = 0x1000;

KCodeSet* FindTitleCodeSet(u64 title_id)
{
    for (unsigned kproc_index = 0; kproc_index < KPROC_NUM; kproc_index++) {
        KProcess* curr_kproc = (KProcess*)(KPROC_START + KPROC_SIZE * kproc_index);
        KCodeSet* curr_codeset = curr_kproc->code_set;
        if (curr_codeset != nullptr && curr_codeset->title_id == title_id)
            return curr_codeset;
    }
    return nullptr;
}

u32 FindCodeOffsetKAddr(KCodeSet* code_set, u32 code_offset)
{
    u32 curr_offset = 0;

    if (code_set == nullptr)
        return 0;

    KLinkedListNode* node = code_set->text_info.first_node;

    // Iterate through all the blocks in the codeset
    do {
        KBlockInfo* block_info = (KBlockInfo*)node->data;
        u32 block_size = block_info->page_count * PAGE_SIZE;

        // The code offset is within this block
        if (code_offset > curr_offset && code_offset < curr_offset + block_size)
            return block_info->mem_section_start + (code_offset - curr_offset);

        // Current offset: amount of bytes searched so far
        curr_offset += block_size;
        node = node->next;
    } while (node->next != nullptr);

    return 0;
}