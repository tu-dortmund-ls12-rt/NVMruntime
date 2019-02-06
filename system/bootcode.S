.global system_entry

system_entry:
    ldr x0, =__stack_top
    mov sp, x0
    bl init_system_c