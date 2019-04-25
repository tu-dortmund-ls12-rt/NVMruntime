#ifndef SYSTEM_MEMORY_STACK_BALANCER
#define SYSTEM_MEMORY_STACK_BALANCER

#include <system/stdint.h>

class StackBalancer {
   public:
    StackBalancer();

    static StackBalancer instance;

    void *setup_shadow_stack(void *phys_head, uint64_t size);

    void trigger_on_interrupt(uint64_t *saved_stack_base);

    void print_statistic();

   private:
    void perform_irq_relocation(uint64_t *saved_stack_base);

    uint64_t relocation_count_syn = 0;
    uint64_t relocation_coint_irq = 0;
};

#endif