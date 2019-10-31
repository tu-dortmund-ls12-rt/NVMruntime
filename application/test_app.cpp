#include <system/syscall_interface.h>
void run_disjkstra();

void app_init() {
    run_disjkstra();
    syscall_shutdown();
}
