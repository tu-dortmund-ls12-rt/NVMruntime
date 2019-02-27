#include "syscall.h"
#include "memory/WriteMonitor.h"
#include "system/service/logger.h"

Syscall Syscall::instance;

void Syscall::stop_system() {
    log("Applocation called stop syscall. Bye :)");
    WriteMonitor::instance.terminate();
    WriteMonitor::instance.plot_results();
    log("ByeBye");
    while (1)
        ;
}