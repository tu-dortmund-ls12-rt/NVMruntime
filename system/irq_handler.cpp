#include <system/service/logger.h>
#include <system/driver/GIC_Interrupts.h>

extern "C" void handle_irq_lowlevel_sync(){
    log("Sync IRQ Occured");
    while(1);
}

extern "C" void handle_irq_lowlevel_irq(){
    log("IRQ Occured");
    while(1);
}

extern "C" void handle_irq_lowlevel_fiq(){
    // log("FIQ Occured");
    GIC_Interrupts::instance.trigger_irq();
}

extern "C" void handle_irq_lowlevel_error(){
    log("Error IRQ Occured");
    while(1);
}