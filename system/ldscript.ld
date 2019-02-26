ENTRY(system_entry)

SECTIONS
{
    . = 0x80000000;
    __NVMSYMBOL_SYSTEM_MEMORY_OFFSET = .;

    __NVMSYMBOL__DRIVER_BEGIN = .;
    __bootcode : {
        build/system/bootcode.o(*)
    }

    __system_tools : {
        build/system/driver/PL011.o(.text)
        build/system/driver/PL011.o(.data)
        build/system/driver/PL011.o(.bss)
        build/system/service/OutputStream.o(.text)
        build/system/service/OutputStream.o(.data)
        build/system/service/OutputStream.o(.bss)
        build/system/driver/GIC.o(.text)
        build/system/driver/GIC.o(.data)
        build/system/driver/GIC.o(.bss)
        build/system/driver/PMC.o(.text)
        build/system/driver/PMC.o(.data)
        build/system/driver/PMC.o(.bss)

        build/system/driver/GIC_Interrupts.o(.text)
        build/system/driver/GIC_Interrupts.o(.data)
        build/system/driver/GIC_Interrupts.o(.bss)

        build/system/memory/MMU.o(.text)
        build/system/memory/MMU.o(.data)
        build/system/memory/MMU.o(.bss)
        build/system/memory/WriteMonitor.o(.text)
        build/system/memory/WriteMonitor.o(.data)
        build/system/memory/WriteMonitor.o(.bss)

        build/system/interrupt.o(*)
        build/system/irq_handler.o(*)

        build/system/init_system.o(*)
    }
    __NVMSYMBOL__DRIVER_END = .;

    __NVMSYMBOL_BOOTSTACK_BEGIN =.;
    .bootstack : {
        . = ALIGN(0x8);
        . += 0x1000; /* 1MB */
        __bootstack_top = .;
    }
    __NVMSYMBOL_BOOTSTACK_END =.;

    __NVMSYMBOL__APPLICATION_INIT_FINI_BEGIN = .;
    .init_array     :
    {
       __init_array_start = .;
       KEEP (*(SORT(.init_array.*)))
       KEEP (*(.init_array))
       KEEP (*(".ctors"))
       KEEP (*(".ctor"))
       __init_array_end = .;
    }

    .fini_array     :
    {
       __fini_array_start = .;
       KEEP (*(SORT(.fini_array.*)))
       KEEP (*(.fini_array))
       KEEP (*(".dtors"))
       KEEP (*(".dtor"))
       __fini_array_end = .;
    }
    __NVMSYMBOL__APPLICATION_INIT_FINI_END = .;

    __NVMSYMBOL__APPLICATION_TEXT_BEGIN = .;
    .text : {
        *(.text)
    }
    __NVMSYMBOL__APPLICATION_TEXT_END = .;

    __NVMSYMBOL__APPLICATION_DATA_BEGIN = .;
    .data : {
        *(.data)
    }
    __NVMSYMBOL__APPLICATION_DATA_END = .;

    .note : {
        *(".note.*")
        *(.eh_frame)
        *(.rodata)
    }

    . += 0x8;

    __NVMSYMBOL__APPLICATION_BSS_BEGIN = .;
    .bss : {
        *(.bss)
    }
    __NVMSYMBOL__APPLICATION_BSS_END = .;
    
    . = ALIGN(0x40);

    __NVMSYMBOL__APPLICATION_STACK_BEGIN = .;
    .stack : {
        . = ALIGN(0x8);
        . += 0x1000; /* 1MB */
        __stack_top = .;
    }
    __NVMSYMBOL__APPLICATION_STACK_END = .;

    PROVIDE (end = .);
}