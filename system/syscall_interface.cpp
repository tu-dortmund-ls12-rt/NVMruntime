#include "syscall_interface.h"

void syscall_exit() { asm volatile("svc #0"); }

#ifdef STACK_BALANCIMG
void syscall_delay_relocation() { asm volatile("svc #1"); }
void syscall_continue_relocatuion() { asm volatile("svc #2"); }
#endif