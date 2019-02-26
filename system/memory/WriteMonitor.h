#ifndef SYSTEM_MEMORY_WRITE_MONITOR
#define SYSTEM_MEMORY_WRITE_MONITOR

class WriteMonitor {
   public:
    static WriteMonitor instance;

    bool handle_data_permission_interrupt();
};

#endif