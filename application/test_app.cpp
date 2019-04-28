#include "data.h"
#include "system/data/RBTree.h"
#include "system/service/logger.h"

#include <system/driver/math.h>
#include <system/memory/StackBalancer.h>
#include <system/memory/stack_relocate.h>

void quick_sort(uint64_t *begin, uint64_t *end);

// Some data inside BSS
uint64_t bss_filler[2048];

void app_init() {
    unsigned long sort_size = 5000;
    log("Starting to sort " << dec << sort_size << " numbers");

    quick_sort(random_number, random_number + sort_size);

    // for (uint64_t i = 0; i < sort_size; i++) {
    //     log(random_number[i]);
    // }

    asm volatile("svc #0");
}

void quick_sort(uint64_t *begin, uint64_t *end) {
    STACK_RECURSIVE_FUNC
    if (begin + 2 >= end) {
        return;
    }
    // log_info("Sorting");
    uint64_t *pivot_element = end - 1;

    uint64_t *li = begin;
    uint64_t *ri = end - 1;

    while (li < ri) {
        while (li < end - 2 && *li < *pivot_element) li++;
        while (ri > begin && *ri >= *pivot_element) ri--;

        if (li < ri) {
            uint64_t buffer = *li;
            *li = *ri;
            *ri = buffer;
        }
    }
    // log_info("Done swapping");

    if (*li > *pivot_element) {
        uint64_t buffer = *li;
        *li = *pivot_element;
        *pivot_element = buffer;
    }

    // log_info("Recursive call");
    quick_sort(begin, li);
    quick_sort(li + 1, end);
}