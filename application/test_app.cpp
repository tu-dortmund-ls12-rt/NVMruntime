void run_disjkstra();

void app_init() {
    asm volatile("svc #10");

    run_disjkstra();
    asm volatile("svc #0");
}