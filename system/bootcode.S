.global system_entry

system_entry:
    ldr x0, =__bootstack_top
    mov sp, x0
    bl init_system_c