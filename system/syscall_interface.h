#ifndef SYSTEM_SYSCALL_INTERFACE
#define SYSTEM_SYSCALL_INTERFACE

void syscall_exit();

#ifdef STACK_BALANCIMG
void syscall_delay_relocation();
void syscall_continue_relocatuion();
#endif

#endif