#include "driver/GIC.h"
#include "driver/GIC_Interrupts.h"
#include "driver/PMC.h"
#include "system/service/logger.h"

GIC400_Distributor gic_distributor;
GIC400_CPU gic_cpu;

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

    gic_distributor.initialize();
    gic_cpu.initialize();
    gic_cpu.setPriotityMask(0xFF);
    GIC_Interrupts::instance.enable(&gic_cpu);

    // Enable CPU Interrupts
    uint64_t spsr_el1;
    asm volatile("mrs %0, spsr_el1" : "=r"(spsr_el1));
    spsr_el1 |= 0b1;  // Use current sp for exceptions
    asm volatile("msr spsr_el1, %0" ::"r"(spsr_el1));
    asm volatile("msr daifclr, #0b1111");

    // Determine number of available performance counters
    uint64_t num_counter = PMC::instance.get_num_available_counters();
    log("Available performance counters: " << num_counter);

    // Test counters
    PMC::instance.set_counters_enabled(true);
    PMC::instance.set_event_counter_enabled(0, true);
    PMC::instance.set_count_event(0, PMC::BUS_ACCESS_STORE);
    PMC::instance.set_el1_counting(0, true);
    PMC::instance.set_non_secure_el1_counting(0, true);
    PMC::instance.enable_overflow_interrupt(0, true);
    gic_distributor.maskInterrupt(320, false);
    PMC::instance.write_event_counter(0, UINT32_MAX - 100);

    volatile uint64_t x = 0;
    for (volatile uint64_t i = 0; i < 2048; i++) {
        x += i;
    }
    PMC::instance.set_event_counter_enabled(0, false);
    uint32_t count = PMC::instance.read_event_counter(0);
    log("Counted in 0: " << count);

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