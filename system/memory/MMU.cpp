#include "MMU.h"
#include <system/service/logger.h>
#include <system/stdint.h>

MMU MMU::instance;

// #define DRAM_SIZE 1073741824  // Maximum 4GB
#define DRAM_SIZE 268435456  // Maximum 4GB

/**
 * Level 0 Table controls 512GB memory
 * =>1 Entry -- 512GB
 */
uint64_t level0_table[1] __attribute__((aligned(4096)));

/**
 * Level 1 Table controls 1GB memory each
 * =>6 Entry -- 6GB
 * The DRAM begins at 2GB Boundary (0x80000000), with 4GB DRAM we need 6 GB VM
 * Spave in total
 */
uint64_t level1_table[6] __attribute__((aligned(4096)));

/**
 * Level 2 Table controls 2MB memory each
 * =>2048 Entry -- 4GB
 * L2 Table begins at 2GB Boundary
 */
uint64_t level2_table[2048] __attribute__((aligned(4096)));

/**
 * Level 3 Table controls 4kb memory each
 * =>DRAM / 4096 Entry
 * L3 Table begins at 2GB Boundary
 */
uint64_t level3_table[DRAM_SIZE / 4096] __attribute__((aligned(4096)));

void MMU::setup_pagetables() {
    /**
     * Some steps required:
     * 1: Set MMU Granularity to 4KB
     * 2: Define memory types
     * 3: Write descriptor entries
     */

    // Set granularity to 4KB
    uint64_t tcr = 0;
    asm volatile("mrs %0, tcr_el1" : "=r"(tcr));
    tcr &= ~(0b11 << 14);
    asm volatile("msr tcr_el1, %0" ::"r"(tcr));

    // Setup memory types. Basically one for dram and one for everything else
    uint8_t normal_outer_inner_wb_transient = 0b01110111;
    uint8_t device_memory = 0b00000000;
    uint64_t mair = 0;
    asm volatile("mrs %0, mair_el1" : "=r"(mair));
    tcr &= ~(0xFFFF);
    tcr |= (device_memory);                         // ATTR0
    tcr |= (normal_outer_inner_wb_transient << 8);  // ATTR1
    asm volatile("msr mair_el1, %0" ::"r"(mair));

    // Setup pagetables
    log("Setting UP Level 0 Table");
    // Begin with level 0
    level0_table[0] = (0b11) | (uint64_t)level1_table;

    log("Setting UP Level 1 Table");
    // Level 1 Table: Blocks for Device memory, Tables for DRAM
    level1_table[0] = (0b01) | (0b0111010000 << 2) | 0x0;
    level1_table[1] = (0b01) | (0b0111010000 << 2) | 0x40000000;
    for (uint64_t i = 0; i < 4; i++) {
        // Table entries, redirecting to level2 table
        level1_table[2 + i] = (0b11) | (((uint64_t)level2_table) + i * 512 * 8);
    }

    log("Setting UP Level 2 Table");
    // Level 2 Table: Completely redirecting to Level 3
    for (uint64_t i = 0; i < 2048; i++) {
        // Table entries, redirecting to level2 table
        level2_table[i] = (0b11) | (((uint64_t)level3_table) + i * 512 * 8);
        if (i % 102 == 0) {
            OutputStream::instance << ".";
        }
    }
    OutputStream::instance << endl;

    log("Setting UP Level 3 Table");
    // Level 3 Table: Normal memory blocks beginning at offset 0x80000000
    for (uint64_t i = 0; i < (DRAM_SIZE / 4096); i++) {
        level3_table[i] =
            (0b01) | (0b0111010001 << 2) | (0x80000000UL + (i * 4096));
        if (i % (DRAM_SIZE / (4096 * 10 * 2)) == 0) {
            OutputStream::instance << ".";
        }
    }
    OutputStream::instance << endl;

    // Finally set the ttbr0 register to level 0 table
    asm volatile("msr ttbr0_el1, %0" ::"r"(level0_table));
}
void MMU::activate_mmu() {
    asm volatile(
        "mrs x0, sctlr_el1;"
        "orr x0, x0, #0x1;"
        "msr sctlr_el1, x0;"
        "dsb sy;"
        "isb;" ::
            : "x0");
}
void MMU::activate_caches() {
    asm volatile(
        "mrs x0, sctlr_el1;"
        "orr x0, x0, #(0x1 << 2);"
        "orr x0, x0, #(0x1 << 12);"
        "msr sctlr_el1, x0;"
        "dsb sy;"
        "isb;" ::
            : "x0");
}
void MMU::clean_and_disable_caches() {
    asm volatile(
        // Deactivate Cache
        "mrs x0, sctlr_el1;"
        "bic x0,x0,#(0x1 << 2);"
        "bic x0,x0,#(0x1 << 12);"
        "msr sctlr_el1, x0;"
        // Invalidate Cache Content
        "mov x0, #0x0;"
        "msr csselr_el1, x0;"
        "mrs x4, ccsidr_el1;"
        "and x1, x4, #0x7;"
        "ldr x3, =0x7FFF;"
        "and x2,x3,x4,lsr #13;"
        "ldr x3, =0x3FF;"
        "and x3,x3,x4,lsr #3;"
        "clz w4,w3;"
        "mov x5, #0;"
        "way_loop:"
        "mov x6, #0;"
        "set_loop:"
        "lsl x7,x5,x4;"
        "orr x7,x0,x7;"
        "lsl x8,x6,x1;"
        "orr x7,x7,x8;"
        "dc cisw, x7;"
        "add x6,x6, #1;"
        "cmp x6,x2;"
        "ble set_loop;"
        "add x5, x5, #1;"
        "cmp x5, x3;"
        "ble way_loop;" ::
            : "x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7", "x8");
}