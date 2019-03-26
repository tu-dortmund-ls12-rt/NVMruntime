#include "syscall.h"
#include "memory/WriteMonitor.h"
#include "system/service/logger.h"

Syscall Syscall::instance;

void Syscall::stop_system() {
    log("Applocation called stop syscall. Bye :)");
#ifdef DO_MONITORING
    WriteMonitor::instance.terminate();
    WriteMonitor::instance.plot_results();
#endif
    log("ByeBye");
    while (1)
        ;
}