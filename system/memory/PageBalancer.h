#include <system/data/RBTree.h>
#include <system/memory/MMU.h>

extern void *__NVMSYMBOL__APPLICATION_TEXT_BEGIN;
extern void *__NVMSYMBOL__APPLICATION_STACK_END;
extern void *__NVMSYMBOL_SPARE_VM_PAGE_BEGIN;

#define MAX_MANAGED_PAGES 256

struct phys_page_handle {
    uintptr_t phys_address;
    uintptr_t mapped_vm_page;
    uint64_t access_count;
};

class PageBalancer {
   public:
    static PageBalancer instance;
    PageBalancer();

    void enable_balancing();

   private:
    struct RBTree<phys_page_handle>::node
        managed_pages[MAX_MANAGED_PAGES];
};