#include "WriteMonitor.h"
#include <system/service/logger.h>
#include <system/stdint.h>

WriteMonitor WriteMonitor::instance;

    bool WriteMonitor::handle_data_permission_interrupt(){
        //Read the fault address
        uint64_t far_el1=0;
        asm volatile("mrs %0, far_el1":"=r"(far_el1));

        log("Data Permission fault at " << hex << far_el1);
        return false;
    }

    void WriteMonitor::handle_pmc_0_interrupt(){
        log("PMC 0 overflowed");
    }