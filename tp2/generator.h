#include "ensitlm.h"
#include "bus.h"

SC_MODULE(generator) {
        ensitlm::initiator_socket<generator> initiador;
        sc_core::sc_in<bool> display_int;
        sc_core::sc_event interrupt_event;

        void behavior(void);
        void interruption(void);
        SC_CTOR(generator);
};
