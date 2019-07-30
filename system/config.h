#ifndef SYSTEM_CONFIG
#define SYSTEM_CONFIG

#define DRAM_SIZE 268435456  // 256MB
#define REAL_STACK_SIZE 0x8000
#define STACK_SIZE (REAL_STACK_SIZE*2)

#define MONITOR_CAPACITY 256
#define SYSTEM_OFFSET 0x80000000
#define MONITORING_RESOLUTION 20000

#define REBALANCE_THRESHOLD 1

// #define DO_REBALANCING
#define DO_MONITORING

// #define RESPECT_PROCESS_VARIATION
// #define PRE_AGED_MEMORY

// #define STACK_BALANCIMG
//The stack pointer must be aligned on 16 bytes
// #define RELOCATION_STEP 0x20
#define RELOCATION_STEP 0x40
#define IN_MEMORY_POINTER_RELOCATION

#define TARGET_STACK_VADDRESS 0x0000000A00000000UL

#endif