#ifndef SYSTEM_MEMORY_WRITE_MONITOR
#define SYSTEM_MEMORY_WRITE_MONITOR

#include <system/stdint.h>

#define MONITOR_CAPACITY 256
#define SYSTEM_OFFSET 0x80000000
#define MONITORING_RESOLUTION 1000

/**
 * The Write Monitor uses some mechanisms to approximate the write count per
 * page. First a performance counter is used to trigger the monitor every nth
 * write. Second the Access Permission Mechanism of the MMU is used to generate
 * interrupts on write accesses.
 */
class WriteMonitor {
   public:
    static WriteMonitor instance;

    void initialize();
    void terminate();
    void plot_results();
    void add_page_to_observe(void *vm_page);

    bool handle_data_permission_interrupt();

    void handle_pmc_0_interrupt();

   private:
    uint64_t write_count[MONITOR_CAPACITY];
    void* vm_pages_to_observe[MONITOR_CAPACITY];
    uint64_t observerd_vm_pages_count = 0;

    // Helper functions
    void set_all_observed_pages(bool generate_interrupt_on_write);
};

#endif