#include "system/service/logger.h"

/**
 * This function is called by the assmebler bootcode
 */
extern "C" void init_system_c() {
    extern void (*__init_array_start)();
    extern void (*__init_array_end)();

    for (void (**actual)() = &__init_array_start; actual < &__init_array_end;
         actual++) {
        (**actual)();
    }
    log("Called init arrays, welcome!");
}