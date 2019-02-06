ENTRY(system_entry)

SECTIONS
{
    . = 0x80000000;
    __bootcode : {
        build/system/bootcode.o(*)
    }

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

    .text : {
        *(.text)
    }
    .data : {
        *(.data)
        *(".note.*")
    }
    .bss : {
        *(.bss)
        
        . = ALIGN(0x8);
        . += 0x100000; /* 1MB */
        __stack_top = .;
    }

    end = .;
}