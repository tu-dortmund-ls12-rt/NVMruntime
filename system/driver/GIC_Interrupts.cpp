#include "GIC_Interrupts.h"
#include <system/service/logger.h>

GIC_Interrupts GIC_Interrupts::instance;

void GIC_Interrupts::enable(GIC400_CPU *cpu_interface) {
    this->cpu_interface = cpu_interface;
}

void GIC_Interrupts::trigger_irq() {
    if (cpu_interface != 0) {
        uint16_t signalled_irq = cpu_interface->raedSignalledInterruptNumber();
        // log("Triggered IRQ" << dec << signalled_irq);
        switch (signalled_irq) {
            case 320:
                handle_irq_320();
                break;
        };
        cpu_interface->signalEndOfInterrupt(signalled_irq);
    }
}

void GIC_Interrupts::handle_irq_320() { 
    //Read the physical address register
    uint64_t par=0;
    asm volatile("mrs %0, par_el1":"=r"(par));
    log("Value in PAR is " << hex << par);
}