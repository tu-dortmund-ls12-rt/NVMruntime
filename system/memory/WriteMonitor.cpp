#include "WriteMonitor.h"
#include <system/service/logger.h>

#include <system/driver/GIC.h>
#include <system/driver/PMC.h>
#include <system/memory/MMU.h>

extern GIC400_Distributor gic_distributor;

WriteMonitor WriteMonitor::instance;

void WriteMonitor::initialize() {
    // Set all observed pages not writable
    set_all_observed_pages(true);

    // Initialize the performance counter
    PMC::instance.set_counters_enabled(true);
    PMC::instance.set_event_counter_enabled(0, true);
    PMC::instance.set_count_event(0, PMC::BUS_ACCESS_STORE);
    PMC::instance.set_el1_counting(0, true);
    PMC::instance.set_non_secure_el1_counting(0, true);
    PMC::instance.enable_overflow_interrupt(0, true);
    gic_distributor.maskInterrupt(320, false);
    PMC::instance.write_event_counter(0, UINT32_MAX - MONITORING_RESOLUTION);
}
void WriteMonitor::terminate() {
    gic_distributor.maskInterrupt(320, true);
    set_all_observed_pages(false);
    PMC::instance.enable_overflow_interrupt(0, false);
    PMC::instance.set_event_counter_enabled(0, false);
}
void WriteMonitor::plot_results() {
    for (uint64_t i = 0; i < MONITOR_CAPACITY; i++) {
        OutputStream::instance << hex << (SYSTEM_OFFSET + i * 0x1000) << " "
                               << dec << write_count[i] << endl;
    }
}
void WriteMonitor::add_page_to_observe(void *vm_page) {
    if (observerd_vm_pages_count >= MONITOR_CAPACITY) {
        log_error("Cannot monitor more than "
                  << MONITOR_CAPACITY
                  << " Pages. Please increase the capacity or remove pages");
        while (1)
            ;
    }
    vm_pages_to_observe[observerd_vm_pages_count++] = vm_page;
}

void WriteMonitor::set_all_observed_pages(bool generate_interrupt_on_write) {
    for (uint64_t i = 0; i < observerd_vm_pages_count; i++) {
        if (generate_interrupt_on_write)
            MMU::instance.set_access_permission(
                vm_pages_to_observe[i], MMU::ACCESS_PERMISSION::R_FROM_EL1);
        else
            MMU::instance.set_access_permission(
                vm_pages_to_observe[i], MMU::ACCESS_PERMISSION::RW_FROM_EL1);
    }
    MMU::instance.flush_tlb();
}

bool WriteMonitor::handle_data_permission_interrupt() {
    // Read the fault address
    uint64_t far_el1 = 0;
    asm volatile("mrs %0, far_el1" : "=r"(far_el1));

    log("Data Permission fault at " << hex << far_el1);
    uintptr_t fault_page = far_el1 & ~(0xFFF);
    write_count[(uint64_t)(MMU::instance.get_mapping((void *)fault_page))]++;

    MMU::instance.set_access_permission((void *)fault_page,
                                        MMU::ACCESS_PERMISSION::RW_FROM_EL1);
    MMU::instance.invalidate_tlb_entry((void *)fault_page);
    return false;
}

void WriteMonitor::handle_pmc_0_interrupt() {
    log("PMC 0 overflowed");
    // Simply reset all acces permissions to generate interrupts
    set_all_observed_pages(true);
}