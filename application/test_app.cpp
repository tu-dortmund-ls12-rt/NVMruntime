#include "data.h"
#include "pfor.h"
#include <system/memory/StackBalancer.h>

uint64_t benchmark();

void app_init() {
    // uint64_t sum =
    benchmark();

    // std::cout << "Overall sum is " << std::dec << sum << std::endl;
    asm("svc #0");
}

void process_sum(uint64_t step_size, uint64_t& next_exception,
                 uint64_t compressed_size, uint64_t& exception_offset,
                 uint32_t& overall_sum, uint64_t i) {
    uint64_t uncompressed[step_size];
    uint64_t number_exceptions = 0;
    next_exception =
        pfor_uncompress(pfor_d_compressed + (i * compressed_size), step_size,
                        pfor_d_exception_list + exception_offset,
                        next_exception, uncompressed, &number_exceptions);
    exception_offset += number_exceptions;

    // Loop over uncompressed data and aggregate
    for (uint64_t x = 0; x < step_size; x++) {
        if (uncompressed[x] != random_number[(step_size * i) + x]) {
            // log_error("Found mismatch");
            // while (1)
            //     ;
        }
        overall_sum += uncompressed[x];
    }
}

uint64_t benchmark() {
    /**
     * This benchmark decompresses pfor data in small packets and aggregatves
     * over them
     */
    uint64_t step_size = 64;
    uint64_t runs = 8000 / step_size;
    uint64_t compressed_size = step_size / 4;
    uint64_t repetitions = 10;

    uint32_t __attribute__((aligned(8))) overall_sum = 0;

    for (uint64_t rep = 0; rep < repetitions; rep++) {
        uint64_t next_exception = pfor_d_first_exception;
        uint64_t exception_offset = 0;
        for (uint64_t i = 0; i < runs; i++) {
            process_sum(step_size, next_exception, compressed_size,
                        exception_offset, overall_sum, i);
            SHint
        }
    }

    // log_info("Uncompressed sum is " << dec << overall_sum);
    return overall_sum;
}