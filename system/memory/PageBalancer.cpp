#include "PageBalancer.h"

#include <system/service/logger.h>
#include "WriteMonitor.h"

template class Node_Comparator<phys_page_handle>;
template <>
int Node_Comparator<phys_page_handle>::compare(phys_page_handle node1,
                                               phys_page_handle node2) {
    if (node2.access_count != node1.access_count) {
        return node1.access_count - node2.access_count;
    }
    return node1.phys_address -
           node2.phys_address;  // Just to keep an absolute ordner in the tree
}
template <>
bool Node_Comparator<phys_page_handle>::equals(phys_page_handle node1,
                                               phys_page_handle node2) {
    return node1.access_count == node2.access_count &&
           node1.phys_address == node2.phys_address;
}

PageBalancer PageBalancer::instance;

PageBalancer::PageBalancer() {
    // Create nodes for all managed pages and add them to a tree
    uintptr_t managed_pages_begin =
        (uintptr_t)(&__NVMSYMBOL__APPLICATION_TEXT_BEGIN);
    uintptr_t managed_pages_end =
        (uintptr_t)(&__NVMSYMBOL__APPLICATION_STACK_END);

    for (uint64_t i = 0; i < MAX_MANAGED_PAGES; i++) {
        managed_pages[i] = {managed_pages_begin, managed_pages_begin, 0};
        aes_tree.insert(managed_pages + i);
        managed_pages_begin += 0x1000;
        if (managed_pages_begin == managed_pages_end) {
            break;
        }
    }
    if (managed_pages_begin < managed_pages_end) {
        log_error("Not enough balancing capacity for the application pages");
        while (1)
            ;
    }
}

void PageBalancer::trigger_rebalance(void *vm_page) {
    uintptr_t managed_pages_begin =
        (uintptr_t)(&__NVMSYMBOL__APPLICATION_TEXT_BEGIN);

    log_info("Trigger rebalance for " << vm_page);
    // Get the target node out of the RBTree
    phys_page_handle target = aes_tree.pop_minimum();
    log("Target should be " << target.phys_address);

    if (target.mapped_vm_page == (uintptr_t)vm_page) {
        // The page cannot be at any better physical location
        // Reinsert the page into the tree
        unsigned int array_offset = target.phys_address - managed_pages_begin;
        aes_tree.insert(managed_pages + array_offset);
        return;
    }

    // Determine the current physical address
    uintptr_t physical_address = (uintptr_t)MMU::instance.get_mapping(vm_page);
    unsigned int array_offset = physical_address - managed_pages_begin;
    // Swap both pages
    uintptr_t former_vm = target.mapped_vm_page;
    managed_pages[array_offset].value.mapped_vm_page = former_vm;
    target.mapped_vm_page = (uintptr_t)vm_page;

    // Exchange pagetables
    MMU::instance.set_page_mapping(vm_page, (void *)target.phys_address);
    MMU::instance.set_page_mapping((void *)former_vm, (void *)physical_address);

    // Last copy the actual data
    uint64_t *n_page_ptr = (uint64_t *)vm_page;
    uint64_t *o_page_ptr = (uint64_t *)former_vm;
    uint64_t *spare = (uint64_t *)(&__NVMSYMBOL_SPARE_VM_PAGE_BEGIN);

    for (uint64_t i = 0; i < 512; i++) {
        spare[i] = n_page_ptr[i];
    }
    for (uint64_t i = 0; i < 512; i++) {
        n_page_ptr[i] = o_page_ptr[i];
    }
    for (uint64_t i = 0; i < 512; i++) {
        o_page_ptr[i] = spare[i];
    }
}

void PageBalancer::enable_balancing() {
    log("RBTree manages " << aes_tree.get_element_count() << " elements");
    uintptr_t managed_pages_begin =
        (uintptr_t)(&__NVMSYMBOL__APPLICATION_TEXT_BEGIN);
    uintptr_t managed_pages_end =
        (uintptr_t)(&__NVMSYMBOL__APPLICATION_STACK_END);

    for (; managed_pages_begin < managed_pages_end;
         managed_pages_begin += 0x1000) {
        WriteMonitor::instance.add_page_to_observe((void *)managed_pages_begin);
    }
    WriteMonitor::instance.set_notify_threshold(REBALANCE_THRESHOLD);
    WriteMonitor::instance.initialize();
}