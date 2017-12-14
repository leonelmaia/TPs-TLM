#include "generator.h"
#include "ensitlm.h"
#include "LCDC_registermap.h"
#include "LCDC.h"

#define BASE_MEMORY_ADDRESS 0x10000000
#define BASE_MEMORY_ADDRESS_VIDEO 0x10001400
#define BASE_LCDC_ADDRESS 0x00000000
#define VALUE_TRIGGER_START 0x00000001
#define BASE_MEMORY_ROM_ADDRESS 0x20000000
#define INT_SIGNAL 0x00000000

using namespace ensitlm;
using namespace std;

void generator::behavior() {
        addr_t addressMemoryVideo = BASE_MEMORY_ADDRESS_VIDEO;
        addr_t addressMemoryRom = BASE_MEMORY_ROM_ADDRESS;
        data_t valueRom,writeValue;
        data_t shiftedDataRom,firstPixelRom,secondPixelRom,thirdPixelRom,lastPixelRom;
        int imageVariation = 0;

        initiador.write(LCDC_ADDR_REG ,BASE_MEMORY_ADDRESS_VIDEO);
        initiador.write(LCDC_START_REG ,VALUE_TRIGGER_START);

        while(true){
                addressMemoryRom = BASE_MEMORY_ROM_ADDRESS;
                addressMemoryVideo = BASE_MEMORY_ADDRESS_VIDEO;
                for(int i = 0 ;i < 9600 ;i++) {
                        initiador.read(addressMemoryRom,valueRom);
                        shiftedDataRom = valueRom >> 16;
                        firstPixelRom= shiftedDataRom & 0xFFFFF000;
                        secondPixelRom = shiftedDataRom & 0xFFFF0F00;
                        thirdPixelRom = shiftedDataRom & 0xFFFF00F0;
                        lastPixelRom= shiftedDataRom & 0xFFFF000F;
                        writeValue = (firstPixelRom<<16) | (secondPixelRom<<12) |
                                     (thirdPixelRom<<8)  | (lastPixelRom<<4);
                        writeValue = writeValue + imageVariation;
                        initiador.write(addressMemoryVideo,writeValue);
                        addressMemoryVideo = addressMemoryVideo + 4;

                        shiftedDataRom = valueRom << 16;
                        firstPixelRom = shiftedDataRom & 0xF000FFFF;
                        secondPixelRom = shiftedDataRom & 0x0F00FFFF;
                        thirdPixelRom = shiftedDataRom & 0x00F0FFFF;
                        lastPixelRom = shiftedDataRom & 0x000FFFFF;
                        writeValue = (firstPixelRom) | (secondPixelRom>>4) |
                                     (thirdPixelRom >>8) |(lastPixelRom>>12);
                        writeValue = writeValue + imageVariation;
                        initiador.write(addressMemoryVideo,writeValue);
                        addressMemoryVideo = addressMemoryVideo + 4;
                        addressMemoryRom = addressMemoryRom + 4;
                }
        wait(interrupt_event);
	cout << "INTERRUPTION" << endl;
	imageVariation += 0x0000AAAA;
        }
}

generator::generator(sc_core::sc_module_name  name)
: sc_core::sc_module(name) {
        SC_THREAD(behavior);
        SC_METHOD(interruption);
	sensitive << display_int;
}

void generator::interruption() {
        interrupt_event.notify();
        initiador.write(LCDC_INT_REG ,INT_SIGNAL);
}
