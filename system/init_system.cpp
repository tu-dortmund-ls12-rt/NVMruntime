#include "system/service/logger.h"

extern void app_init();

/**
 * This function is called by the assmebler bootcode
 */
extern "C" void init_system_c() {
    extern void (*__init_array_start)();
    extern void (*__init_array_end)();

    for (void (**actual)() = &__init_array_start; actual < &__init_array_end;
         actual++) {
        (**actual)();
    }
    log("Called init arrays, welcome!");

    // Determine the running exception level
    uint64_t current_el_value = 0;
    asm volatile("mrs %0, currentel" : "=r"(current_el_value));
    log("Running on Excpetion Level " << (current_el_value >> 2));

    // Determine number of available performance counters
    uint64_t hdcr_value = 5;
    asm volatile("mrs %0, pmcr_el0" : "=r"(hdcr_value));
    log("Available performance counters: "
        << dec << ((hdcr_value & (0b11111 << 11)) >> 11));

    log("Clearing the BSS");
    extern unsigned long __NVMSYMBOL__APPLICATION_BSS_BEGIN;
    extern unsigned long __NVMSYMBOL__APPLICATION_BSS_END;
    unsigned long bss_size = ((uint64_t)(&__NVMSYMBOL__APPLICATION_BSS_END)) -
                             ((uint64_t)(&__NVMSYMBOL__APPLICATION_BSS_BEGIN));
    unsigned long *last_dot = &__NVMSYMBOL__APPLICATION_BSS_BEGIN;

    for (unsigned long *actual = &__NVMSYMBOL__APPLICATION_BSS_BEGIN;
         actual < &__NVMSYMBOL__APPLICATION_BSS_END; actual++) {
        *actual = 0;

        if ((uint64_t)actual - (uint64_t)last_dot > bss_size / 10) {
            last_dot = actual;
            OutputStream::instance << ".";
        }
    }
    OutputStream::instance << "\n";
    log("Cleared the BSS");

    log("Calling target app (with swapped stack pointer)");
    asm volatile(
        "ldr x0, =__stack_top;"
        "mov x1, sp;"
        "mov sp, x0;"
        "str x1, [sp, #-8];"
        "sub sp, sp, #16;"
        "blr %0;"
        "add sp, sp, #8;"
        "ldr x1, [sp, #0];"
        "mov sp, x1;" ::"r"(&app_init)
        : "x0", "x1");
    log("App returned, exiting. Bye");
}