#include "syscall.h"
#include "memory/WriteMonitor.h"
#include "system/service/logger.h"
#include "memory/PageBalancer.h"

Syscall Syscall::instance;

void Syscall::stop_system() {
    log("Applocation called stop syscall. Bye :)");
#ifdef DO_MONITORING
    WriteMonitor::instance.terminate();
    // WriteMonitor::instance.plot_results();
#endif
#ifdef DO_REBALANCING
    log("Rebalance count:" << dec
                           << PageBalancer::instance.get_rebalance_count());
#endif
    log("ByeBye");
    while (1)
        ;
}