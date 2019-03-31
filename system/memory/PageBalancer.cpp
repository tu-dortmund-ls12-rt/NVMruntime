#include "PageBalancer.h"

#include <system/service/logger.h>
#include "WriteMonitor.h"

PageBalancer PageBalancer::instance;

PageBalancer::PageBalancer() {
    // Create nodes for all managed pages and add them to a tree
    uintptr_t managed_pages_begin =
        (uintptr_t)(&__NVMSYMBOL__APPLICATION_INIT_FINI_BEGIN);
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
        (uintptr_t)(&__NVMSYMBOL__APPLICATION_INIT_FINI_BEGIN);
    // Get the target node out of the RBTree
    phys_page_handle target = aes_tree.pop_minimum();
    // log("[RMAP] " << vm_page << "{" << MMU::instance.get_mapping(vm_page)
    //               << "} -> " << hex << target.phys_address << "{" << hex
    //               << target.mapped_vm_page << "}");

    if (target.mapped_vm_page == (uintptr_t)vm_page) {
        // The page cannot be at any better physical location
        // Reinsert the page into the tree
        unsigned int array_offset =
            (target.phys_address - managed_pages_begin) / 0x1000;
        aes_tree.insert(managed_pages + array_offset);
        return;
    }

    rebalance_count++;

    // Determine the current physical address
    uintptr_t physical_address = (uintptr_t)MMU::instance.get_mapping(vm_page);
    unsigned int array_offset =
        (physical_address - managed_pages_begin) / 0x1000;
    // Swap both pages
    uintptr_t former_vm = target.mapped_vm_page;
    managed_pages[array_offset].value.mapped_vm_page = former_vm;
    target.mapped_vm_page = (uintptr_t)vm_page;

    // Exchange pagetables
    MMU::instance.set_page_mapping(vm_page, (void *)target.phys_address);
    MMU::instance.invalidate_tlb_entry(vm_page);
    MMU::instance.set_page_mapping((void *)former_vm, (void *)physical_address);
    MMU::instance.invalidate_tlb_entry((void *)former_vm);

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

    target.access_count++;
    unsigned int target_array_offset =
        (target.phys_address - managed_pages_begin) / 0x1000;
    managed_pages[target_array_offset].value = target;
    aes_tree.insert(managed_pages + target_array_offset);
}

void PageBalancer::enable_balancing() {
    log("Balancing " << aes_tree.get_element_count() << " pages");
    uintptr_t managed_pages_begin =
        (uintptr_t)(&__NVMSYMBOL__APPLICATION_INIT_FINI_BEGIN);
    uintptr_t managed_pages_end =
        (uintptr_t)(&__NVMSYMBOL__APPLICATION_STACK_END);

    for (; managed_pages_begin < managed_pages_end;
         managed_pages_begin += 0x1000) {
        // log("Adding page " << (void *)managed_pages_begin << " to observe");
        WriteMonitor::instance.add_page_to_observe((void *)managed_pages_begin);
    }
    WriteMonitor::instance.set_notify_threshold(REBALANCE_THRESHOLD);
    WriteMonitor::instance.initialize();
}

uint64_t PageBalancer::get_rebalance_count() { return rebalance_count; }