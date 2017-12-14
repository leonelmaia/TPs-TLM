#include "ensitlm.h"
#include "bus.h"

SC_MODULE(memory) {
        ensitlm::target_socket<memory> target;
        ensitlm::data_t* storage;
        int sizeofMemory;

        tlm::tlm_response_status write(const ensitlm::addr_t &a,
                const ensitlm::data_t &d);

        tlm::tlm_response_status read(const ensitlm::addr_t &a,
                                ensitlm::data_t &d);

        memory(sc_core::sc_module_name name, int taille);
};
