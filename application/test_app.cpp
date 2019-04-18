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
    uint64_t result = 0;
    uint64_t el_count = 8000;
    for (uint64_t i = 0; i < el_count; i++) {
        if (i % 40 == 0) {
            relocate_stack();
        }
        result += (random_number[i] & (0b1 << 0)) != 0;
        result += (random_number[i] & (0b1 << 1)) != 0;
        result += (random_number[i] & (0b1 << 2)) != 0;
        result += (random_number[i] & (0b1 << 3)) != 0;
        result += (random_number[i] & (0b1 << 4)) != 0;
        result += (random_number[i] & (0b1 << 5)) != 0;
        result += (random_number[i] & (0b1 << 6)) != 0;
        result += (random_number[i] & (0b1 << 7)) != 0;
    }
    asm volatile("svc #0");
}