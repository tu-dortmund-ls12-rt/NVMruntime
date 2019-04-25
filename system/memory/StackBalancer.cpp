#include "StackBalancer.h"
#include <system/service/logger.h>
#include "MMU.h"

StackBalancer StackBalancer::instance;

StackBalancer::StackBalancer() {}

void *StackBalancer::setup_shadow_stack(void *phys_head, uint64_t size) {
    uint64_t v_stack_begin = TARGET_STACK_VADDRESS;
    uint64_t phys_begin = ((uint64_t)(phys_head)) - size;
    for (uint64_t i = 0; i < (size / 4096); i++) {
        MMU::instance.set_stack_page_mapping((void *)v_stack_begin,
                                             (void *)phys_begin);
        // log_info("MAP " << hex << v_stack_begin << " -> " << hex <<
        // phys_begin);
        v_stack_begin += 4096;
        phys_begin += 4096;
    }
    return (void *)(TARGET_STACK_VADDRESS + STACK_SIZE);
}

void StackBalancer::trigger_on_interrupt(uint64_t *saved_stack_base) {
    log_info("Saved stack frame is at " << saved_stack_base);

    log_info("X0\t" << hex << saved_stack_base[28]);
    log_info("X1\t" << hex << saved_stack_base[29]);
    log_info("X2\t" << hex << saved_stack_base[26]);
    log_info("X3\t" << hex << saved_stack_base[27]);
    log_info("X4\t" << hex << saved_stack_base[24]);
    log_info("X5\t" << hex << saved_stack_base[25]);
    log_info("X6\t" << hex << saved_stack_base[22]);
    log_info("X7\t" << hex << saved_stack_base[23]);
    log_info("X8\t" << hex << saved_stack_base[20]);
    log_info("X9\t" << hex << saved_stack_base[21]);
    log_info("X10\t" << hex << saved_stack_base[18]);
    log_info("X11\t" << hex << saved_stack_base[19]);
    log_info("X12\t" << hex << saved_stack_base[16]);
    log_info("X13\t" << hex << saved_stack_base[17]);
    log_info("X14\t" << hex << saved_stack_base[14]);
    log_info("X15\t" << hex << saved_stack_base[15]);
    log_info("X16\t" << hex << saved_stack_base[12]);
    log_info("X17\t" << hex << saved_stack_base[13]);
    log_info("X18\t" << hex << saved_stack_base[10]);
    log_info("X19\t" << hex << saved_stack_base[11]);
    log_info("X20\t" << hex << saved_stack_base[8]);
    log_info("X21\t" << hex << saved_stack_base[9]);
    log_info("X22\t" << hex << saved_stack_base[6]);
    log_info("X23\t" << hex << saved_stack_base[7]);
    log_info("X24\t" << hex << saved_stack_base[4]);
    log_info("X25\t" << hex << saved_stack_base[5]);
    log_info("X26\t" << hex << saved_stack_base[2]);
    log_info("X27\t" << hex << saved_stack_base[3]);
    log_info("X28\t" << hex << saved_stack_base[0]);
    log_info("X29\t" << hex << saved_stack_base[30]);
    log_info("X30\t" << hex << saved_stack_base[1]);

    while (1)
        ;
}