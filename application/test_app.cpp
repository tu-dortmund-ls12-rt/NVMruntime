#include "data.h"
#include "system/service/logger.h"

void quick_sort(uint8_t *begin, uint8_t *end);

//Some data inside BSS
uint64_t bss_filler[256];

void app_init() {
    for (uint32_t i = 0; i < 10; i++) {
        log(random_number[i]);
    }
    log_info("Sorting 10 numbers");
    //quick_sort(random_number, random_number + 10);
    for (uint32_t i = 0; i < 10; i++) {
        log(random_number[i]);
    }
}

void quick_sort(uint8_t *begin, uint8_t *end) {
    if (begin + 1 == end) {
        return;
    }
    uint64_t pivot_index = (((uint64_t)end) - ((uint64_t)begin)) / 2;
    uint8_t pivot_element = begin[pivot_index];

    uint8_t *li = begin;
    uint8_t *ri = end - 1;

    while (li < ri) {
        while (li < end - 1 && *li < pivot_element) li++;
        while (ri > begin && *ri >= pivot_element) ri--;

        if (li < ri) {
            uint8_t buffer = *li;
            *li = *ri;
            *ri = buffer;
        }
    }

    if (*li > pivot_element) {
        uint8_t buffer = *li;
        *li = begin[pivot_index];
        begin[pivot_index] = buffer;
    }

    quick_sort(begin, li - 1);
    quick_sort(li, end);
}