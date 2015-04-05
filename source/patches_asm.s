.arm
.code 32
.text

.global ret
ret: .word 0

@@-----------------------------------------------------------------------------

.extern self_pid
.extern kproc_codeset_offset

.global PatchPid
.type PatchPid, %function
PatchPid:
    cpsid aif
    push {r1-r2, lr}
    mov r0, #0

    ldr r1, =0xFFFF9004          @@ Load pointer to current KProcess
    ldr r1, [r1]
    ldr r2, =kproc_codeset_offset
    ldr r2, [r2]

    str r0, [r1, r2]             @@ *CURR_KPROC_PTR = 0
    pop {r1-r2, pc}

.global UnpatchPid
.type UnpatchPid, %function
UnpatchPid:
    cpsid aif
    push {r1-r2, lr}

    ldr r0, =0xFFFF9004         @@ Load pointer to current KProcess
    ldr r0, [r0]
    ldr r1, =self_pid
    ldr r1, [r1]
    ldr r2, =kproc_codeset_offset
    ldr r2, [r2]

    str r1, [r0, r2]            @@ *CURR_KPROC_PTR = self_pid

    mov r0, #0
    pop {r1-r2, pc}

@@-----------------------------------------------------------------------------

.extern PatchProcess

.global PatchProcessWrapper
.type PatchProcessWrapper, %function
PatchProcessWrapper:
    cpsid aif
    push {r1, lr}
    
    blx PatchProcess

    ldr r1, =ret
    str r0, [r1]

    pop {r1, pc}