#ifndef SYSTEM_MEMORY_STACK_BALANCER
#define SYSTEM_MEMORY_STACK_BALANCER

#include <system/stdint.h>

#define STACK_OUTER_LOOP StackBalancer::instance.outer_loop_automatic();

class StackBalancer {
   public:
    StackBalancer();

    static StackBalancer instance;

    void *setup_shadow_stack(void *phys_head, uint64_t size);

    void trigger_on_interrupt(uint64_t *saved_stack_base);

    void hint_relocation();

    void print_statistic();

    void outer_loop_automatic();

   private:
    void perform_irq_relocation(uint64_t *saved_stack_base);

    uint64_t relocation_count_syn = 0;
    uint64_t relocation_coint_irq = 0;

    bool performed_since_last_irq = false;
    bool performing_balane = false;
    bool performed_irq_version=false;

    uint64_t outer_loop_balancing_ratio = 1;
    uint64_t outer_loop_cycle = 0;
};

#endif