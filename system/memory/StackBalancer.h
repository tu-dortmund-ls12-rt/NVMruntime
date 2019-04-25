#ifndef SYSTEM_MEMORY_STACK_BALANCER
#define SYSTEM_MEMORY_STACK_BALANCER

#include <system/stdint.h>

class StackBalancer {
   public:
    StackBalancer();

    static StackBalancer instance;

    void *setup_shadow_stack(void *phys_head, uint64_t size);

    void trigger_on_interrupt(uint64_t *saved_stack_base);
};

#endif