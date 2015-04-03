.arm
.code 32
.text

.global ret
ret: .word 0

@@-----------------------------------------------------------------------------

.extern self_pid

.global patch_pid
.type patch_pid, %function
patch_pid:
    cpsid aif
    push {r1-r2, lr}
    mov r0, #0

    ldr r1, =0xFFFF9004          @@ Load pointer to current KProcess
    ldr r1, [r1]
    ldr r2, =0xB4                @@ Load KProcess PID offset

    str r0, [r1, r2]             @@ *CURR_KPROC_PTR = 0
    pop {r1-r2, pc}

.global unpatch_pid
.type unpatch_pid, %function
unpatch_pid:
    cpsid aif
    push {r1-r2, lr}

    ldr r0, =0xFFFF9004         @@ Load pointer to current KProcess
    ldr r0, [r0]
    ldr r1, =self_pid
    ldr r1, [r1]
    ldr r2, =0xB4               @@ 0xB4 - KProcess PID offset

    str r1, [r0, r2]            @@ *CURR_KPROC_PTR = self_pid

    mov r0, #0
    pop {r1-r2, pc}

@@-----------------------------------------------------------------------------

.extern patch_process

.global patch_process_wrapper
.type patch_process_wrapper, %function
patch_process_wrapper:
    cpsid aif
    push {r1, lr}
    
    blx patch_process

    ldr r1, =ret
    str r0, [r1]

    pop {r1, pc}