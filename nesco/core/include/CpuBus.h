#ifndef NESCO_BUS_H
#define NESCO_BUS_H

#include "Ram.h"
#include "Ppu.h"

namespace nesco::core
{
    class CpuBus
    {
    public:
        CpuBus(Ram *_ram, Ppu *_ppu);
        ~CpuBus();

        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t data);

    private:
        Ram *ram;
        Ppu *ppu;
    };
};

#endif