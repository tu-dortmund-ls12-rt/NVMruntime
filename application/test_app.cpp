#include "data.h"
#include "system/data/RBTree.h"
#include "system/service/logger.h"

void quick_sort(uint8_t *begin, uint8_t *end);

// Some data inside BSS
uint64_t bss_filler[1];

void app_init() {
    log("Testing rbtree, inserting first 20 random numbers");
    RBTree<unsigned int> test_tree;
    RBTree<unsigned int>::node nodes[20];
    for (int i = 0; i < 20; i++) {
        nodes[i].value = random_number[i];
        log("Placing element " << nodes[i].value);
        test_tree.insert(nodes + i);
        // test_tree.print_tree();
    }
    log("Tree now has " << test_tree.get_element_count() << " Elements");
    while (test_tree.get_element_count() > 0) {
        log("Next minimum is " << test_tree.pop_minimum());
    }

    log("Starting to sort " << dec << array_size << " numbers");

    quick_sort(random_number, random_number + array_size);

    asm volatile("svc #0");
    // for (uint64_t i = 0; i < array_size; i++) {
    //     log(random_number[i]);
    // }
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