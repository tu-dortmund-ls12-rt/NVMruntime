#ifndef SYSTEM_SYSCALL
#define SYSTEM_SYSCALL

class Syscall {
   public:
    static Syscall instance;

    void stop_system();
};

#endif