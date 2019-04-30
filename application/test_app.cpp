#include "data.h"
#include "system/data/RBTree.h"
#include "system/service/logger.h"

#include <system/driver/math.h>
#include <system/memory/StackBalancer.h>
#include <system/memory/stack_relocate.h>

void quick_sort_f(uint64_t *begin, uint64_t *end);
void quick_sort_b(uint64_t *begin, uint64_t *end);

// Some data inside BSS
uint64_t bss_filler[2048];

uint64_t sort_buffer[8000];

void app_init() {
    unsigned long sort_size = 5000;
    log("Starting to sort " << dec << sort_size << " numbers");

    // quick_sort_f(random_number, random_number + sort_size);

    for (uint64_t i = 0; i < 20; i++) {
        for (uint64_t x = 0; x < sort_size; x++) {
            STACK_OUTER_LOOP
            sort_buffer[x] = random_number[x];
        }
        quick_sort_f(sort_buffer, sort_buffer + sort_size);
        // for (uint64_t i = 0; i < sort_size; i++) {
        //     log(dec << sort_buffer[i]);
        // }
        // log_info("Sorted fw");

        for (uint64_t x = 0; x < sort_size; x++) {
            STACK_OUTER_LOOP
            sort_buffer[x] = random_number[x];
        }
        quick_sort_b(sort_buffer, sort_buffer + sort_size);
        // for (uint64_t i = 0; i < sort_size; i++) {
        //     log(dec << sort_buffer[i]);
        // }
        // log_info("Sorted bw");
    }

    // for (uint64_t i = 0; i < sort_size; i++) {
    //     log(random_number[i]);
    // }

    asm volatile("svc #0");
}

void quick_sort_f(uint64_t *begin, uint64_t *end) {
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
    quick_sort_f(begin, li);
    quick_sort_f(li + 1, end);
}

void quick_sort_b(uint64_t *begin, uint64_t *end) {
    STACK_RECURSIVE_FUNC
    if (begin + 2 >= end) {
        return;
    }
    // log_info("Sorting");
    uint64_t *pivot_element = end - 1;

    uint64_t *li = begin;
    uint64_t *ri = end - 1;

    while (li < ri) {
        while (li < end - 2 && *li > *pivot_element) li++;
        while (ri > begin && *ri <= *pivot_element) ri--;

        if (li < ri) {
            uint64_t buffer = *li;
            *li = *ri;
            *ri = buffer;
        }
    }
    // log_info("Done swapping");

    if (*li < *pivot_element) {
        uint64_t buffer = *li;
        *li = *pivot_element;
        *pivot_element = buffer;
    }

    // log_info("Recursive call");
    quick_sort_b(begin, li);
    quick_sort_b(li + 1, end);
}