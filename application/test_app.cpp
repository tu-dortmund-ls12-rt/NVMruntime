#include "data.h"
#include "system/service/logger.h"

void quick_sort(uint8_t *begin, uint8_t *end);

// Some data inside BSS
uint64_t bss_filler[1];

void app_init() {
    // log("Starting to sort " << array_size << " numbers");
    quick_sort(random_number, random_number + array_size);
}

void quick_sort(uint8_t *begin, uint8_t *end) {
    if (begin + 2 >= end) {
        return;
    }
    uint8_t *pivot_element = end - 1;

    uint8_t *li = begin;
    uint8_t *ri = end - 1;

    while (li < ri) {
        while (li < end - 2 && *li < *pivot_element) li++;
        while (ri > begin && *ri >= *pivot_element) ri--;

        if (li < ri) {
            uint8_t buffer = *li;
            *li = *ri;
            *ri = buffer;
        }
    }

    if (*li > *pivot_element) {
        uint8_t buffer = *li;
        *li = *pivot_element;
        *pivot_element = buffer;
    }

    quick_sort(begin, li);
    quick_sort(li + 1, end);
}