#ifndef SYSTEM_MEMORY_RELOCATIONSAFEPOINTER
#define SYSTEM_MEMORY_RELOCATIONSAFEPOINTER

#include <system/stdint.h>
#include <system/syscall_interface.h>

#ifdef STACK_BALANCIMG

extern uint64_t __virtual_stack_end;
extern uint64_t __current_stack_base_ptr;

template <typename T>
class RelocationSafePointer {
   private:
    /**
     * The local_ptr stores the pointer itself. The ptr_snapshot_relocation
     * stores the current relocation width, which has to be used later to
     * dereference correctly
     */
    uintptr_t local_ptr;
    uint64_t ptr_snapshot_relocation;

   public:
    RelocationSafePointer() {
        local_ptr = 0;
        ptr_snapshot_relocation = 0;
    }
    RelocationSafePointer(T *ptr) {
        syscall_delay_relocation();

        local_ptr = (uintptr_t)ptr;
        /**
         * Save the internal pointer against relocations by setting the upper
         * bit to one
         */
        local_ptr |= (0b1UL << 63);

        ptr_snapshot_relocation =
            (__virtual_stack_end - __current_stack_base_ptr);

        syscall_continue_relocatuion();
    }

    T operator*() {
        syscall_delay_relocation();

        // Restore the correct pointer
        uintptr_t correct = local_ptr & ~(0b1UL << 63);
        // Determine the current stack relocation
        uint64_t current_relocation =
            (__virtual_stack_end - __current_stack_base_ptr);

        if (current_relocation >= ptr_snapshot_relocation) {
            correct -= (current_relocation - ptr_snapshot_relocation);
        } else {
            // In this case, the relocation wrapped around
            correct += (ptr_snapshot_relocation - current_relocation);
        }

        log_info("CR " << dec << current_relocation << " OR " << dec << ptr_snapshot_relocation);

        T copy = *((T *)(correct));

        syscall_continue_relocatuion();

        return copy;
    }
};

#endif

#endif