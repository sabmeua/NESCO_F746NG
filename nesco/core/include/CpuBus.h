#ifndef NESCO_BUS_H
#define NESCO_BUS_H

#include "Ram.h"
#include "Ppu.h"
#include "Apu.h"
#include "Dma.h"

namespace nesco::core
{
    class CpuBus
    {
    public:
        CpuBus(Ram *_ram, Ppu *_ppu, Apu *_apu, Dma *_dma);
        ~CpuBus();

        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t data);

    private:
        Ram *ram;
        Ppu *ppu;
        Apu *apu;
        Dma *dma;
    };
};

#endif