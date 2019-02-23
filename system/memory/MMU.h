#ifndef SYSTEM_MEMORY_MMU
#define SYSTEM_MEMORY_MMU
class MMU {
   public:
    static MMU instance;

    void setup_pagetables();
    void activate_mmu();
    void activate_caches();
    void clean_and_disable_caches();
};

#endif