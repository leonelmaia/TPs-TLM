#include "memory.h"
#include "bus.h"
#include "ensitlm.h"

using namespace std;

tlm::tlm_response_status memory::write(const ensitlm::addr_t &a,
        const ensitlm::data_t &d) {
        storage[a] = d;
        return tlm::TLM_OK_RESPONSE;
}

tlm::tlm_response_status memory::read(const ensitlm::addr_t &a,
                /* */ ensitlm::data_t &d) {
        d = storage[a];
        return tlm::TLM_OK_RESPONSE;
}

memory::memory(sc_core::sc_module_name  name , int taille): sc_core::sc_module(name) {
        this->sizeofMemory = 4*taille;
        this->storage = (ensitlm::data_t*)malloc(this->sizeofMemory * sizeof(ensitlm::data_t));
}
