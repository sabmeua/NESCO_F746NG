#ifndef NESCO_CORE_CPU_BUS_H
#define NESCO_CORE_CPU_BUS_H

#include "Ram.h"
#include "Ppu.h"
#include "Apu.h"
#include "Dma.h"
#include "Cartridge.h"

namespace nesco::core
{
    class CpuBus
    {
    public:
        CpuBus(Ram *_ram, Ppu *_ppu, Apu *_apu, Dma *_dma);
        ~CpuBus();

        uint8_t read(uint16_t addr);
        uint16_t write(uint16_t addr, uint8_t data);

        void loadCartridge(Cartridge *_cartridge) {
            cartridge = _cartridge;
        }

    private:
        Ram *ram;
        Ppu *ppu;
        Apu *apu;
        Dma *dma;
        Cartridge *cartridge;
    };
};

#endif