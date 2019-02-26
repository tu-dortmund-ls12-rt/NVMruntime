#ifndef SYSTEM_MEMORY_MMU
#define SYSTEM_MEMORY_MMU

#include <system/stdint.h>

class MMU {
   public:
    static MMU instance;

    void setup_pagetables();
    void activate_mmu();
    void activate_caches();
    void clean_and_disable_caches();
    void flush_tlb();
    void set_access_flag(void *vm_page, bool af);
    enum ACCESS_PERMISSION {
        RW_FROM_EL1 = 0b00,
        RW_FROM_EL1_EL0 = 0b01,
        R_FROM_EL1 = 0b10,
        R_FROM_EL1_EL0 = 0b11
    };
    void set_access_permission(void *vm_page, uint64_t ap);
    void *get_mapping(void *vm_page);
};

#endif