#include "syscall.h"
#include "memory/PageBalancer.h"
#include "memory/StackBalancer.h"
#include "memory/WriteMonitor.h"
#include "system/service/logger.h"

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

#ifdef STACK_BALANCIMG
    StackBalancer::instance.print_statistic();
#endif
    log("ByeBye");
    while (1)
        ;
}

#ifdef STACK_BALANCIMG
void Syscall::pause_relocation(uint64_t *saved_stack_base) {
    StackBalancer::instance.paused_relocation = true;
}
void Syscall::resume_relocation(uint64_t *saved_stack_base) {
    StackBalancer::instance.paused_relocation = false;
    if (StackBalancer::instance.irq_while_paused) {
        StackBalancer::instance.irq_while_paused = false;
        StackBalancer::instance.trigger_on_interrupt(saved_stack_base);
    }
}
#endif