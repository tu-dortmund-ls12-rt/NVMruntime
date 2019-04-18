#include "StackBalancer.h"
#include "MMU.h"
#include <system/service/logger.h>

StackBalancer StackBalancer::instance;

StackBalancer::StackBalancer() {}

void *StackBalancer::setup_shadow_stack(void *phys_head, uint64_t size) {
    uint64_t v_stack_begin = TARGET_STACK_VADDRESS;
    uint64_t phys_begin = ((uint64_t)(phys_head)) - size;
    for (uint64_t i = 0; i < (size / 4096); i++) {
        MMU::instance.set_stack_page_mapping((void *)v_stack_begin,
                                             (void *)phys_begin);
        // log_info("MAP " << hex << v_stack_begin << " -> " << hex <<  phys_begin);
        v_stack_begin += 4096;
        phys_begin += 4096;
    }
    return (void *)(TARGET_STACK_VADDRESS + STACK_SIZE);
}