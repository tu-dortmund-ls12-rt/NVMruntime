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

void PageBalancer::trigger_rebalance(void *vm_page){
log_info("Trigger rebalance for " << vm_page);
}

void PageBalancer::enable_balancing() {
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