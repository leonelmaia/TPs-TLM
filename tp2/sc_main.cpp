#include "generator.h"
#include "bus.h"
#include "ensitlm.h"
#include "memory.h"
#include "LCDC.h"
#include "ROM.h"

int main () {
        sc_core::sc_signal< bool ,sc_core::SC_MANY_WRITERS > irq_signal("IRQ");
        sc_core::sc_time display_period = sc_core::sc_time(1.0 / 25, sc_core::SC_SEC);

        generator generator("Generator1");
        Bus bus("Bus");
        memory memory("Memory",76800);
        LCDC LCDC("LCDC" , display_period);
        ROM ROM("ROM");

        bus.map(memory.target, 0x10000000, memory.sizeofMemory);
        bus.map(LCDC.target_socket, 0x00000000 , 12 );
        bus.map(ROM.socket, 0x20000000 , 38400 );

        generator.display_int.bind(irq_signal);
        generator.initiador.bind(bus.target);
        bus.initiator.bind(memory.target);
        bus.initiator.bind(LCDC.target_socket);
        bus.initiator.bind(ROM.socket);
        LCDC.display_int.bind(irq_signal);
        LCDC.initiator_socket.bind(bus.target);

        sc_core::sc_start();

        return 0;
}
