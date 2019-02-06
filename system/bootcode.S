.global system_entry

system_entry:
    ldr x0, =__bootstack
    add x0, x0, #0x1000
    mov sp, x0
    bl init_system_c