#include <system/service/logger.h>
#include "data.h"
#include "pfor.h"

void app_init() {
    log_info("Beginning PFOR Compression");
    log_info("Compressing 16 Numbers:");
    for (uint64_t i = 0; i < 16; i++) {
        log_info(dec << random_number[i]);
    }

    uint64_t compressed[4];
    uint64_t exception_list[16];
    uint64_t first_exception;
    uint64_t exception_count;

    pfor_compress(random_number, 16, compressed, exception_list,
                  &exception_count, &first_exception);

    log_info("Compressed:");
    for (uint64_t i = 0; i < 4; i++) {
        log_info("[" << dec << i << "]:0 " << dec
                     << (((compressed[i]) & (255 << 0)) >> 0));
        log_info("[" << dec << i << "]:1 " << dec
                     << (((compressed[i]) & (255 << 8)) >> 8));
        log_info("[" << dec << i << "]:2 " << dec
                     << (((compressed[i]) & (255 << 16)) >> 16));
        log_info("[" << dec << i << "]:3 " << dec
                     << (((compressed[i]) & (255 << 24)) >> 24));
    }
    log_info("Exceptions:");
    for (uint64_t i = 0; i < exception_count; i++) {
        log_info("[" << dec << i << "] " << dec << exception_list[i]);
    }
    log_info("First exception at " << dec << first_exception);

    log_info("\n=====Decompressing=====\n");
    uint64_t decompressed[10];
    pfor_uncompress(compressed, 16, exception_list, first_exception,
                    decompressed);

    for (uint64_t i = 0; i < 16; i++) {
        log_info("[" << dec << i << "] " << dec << decompressed[i]);
    }

    asm volatile("svc #0");
}