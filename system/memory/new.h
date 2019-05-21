#ifndef SYSTEM_MEMORY_NEW
#define SYSTEM_MEMORY_NEW

#include <system/stdint.h>

void *operator new(uint64_t size, void *placement);

#endif