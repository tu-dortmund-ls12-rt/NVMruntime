#include "system/data/RBTree.h"
#include "system/service/logger.h"

#include <system/driver/math.h>
#include "data.h"
#include "stack_relocate.h"

// Some data inside BSS
uint64_t bss_filler[2048];

uint64_t bitcount(uint8_t *data, uint64_t el_count);
void do_bitcount();

extern uint64_t __current_stack_base_ptr;

void app_init() {
    volatile uint64_t tests[5] = {1, 2, 3, 4, 5};
    volatile uint64_t test = 52;
    volatile uint64_t *ptr = &test;
    while (1) {
        log_info("\n(" << (void *)ptr << ") - [" << dec << *ptr << "]");
        log_info("Base at " << hex << __current_stack_base_ptr);
        relocate_stack();
    }
    do_bitcount();
    log_info(tests[1]);
    asm volatile("svc #0");
}

void do_bitcount() {
    uint64_t number = 4000;
    log("Calculating bitcount for " << dec << number << " values");

    uint64_t count = bitcount(random_number, number);

    log("Counted " << count << " bits");
}

uint64_t bitcount(uint8_t *data, uint64_t el_count) {
    uint64_t result = 0;
    for (uint64_t i = 0; i < el_count; i++) {
        result += (data[i] & (0b1 << 0)) != 0;
        result += (data[i] & (0b1 << 1)) != 0;
        result += (data[i] & (0b1 << 2)) != 0;
        result += (data[i] & (0b1 << 3)) != 0;
        result += (data[i] & (0b1 << 4)) != 0;
        result += (data[i] & (0b1 << 5)) != 0;
        result += (data[i] & (0b1 << 6)) != 0;
        result += (data[i] & (0b1 << 7)) != 0;
    }
    return result;
}
