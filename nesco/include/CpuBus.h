#ifndef NESCO_BUS_H
#define NESCO_BUS_H

#include "Ram.h"

namespace nesco
{
    class CpuBus
    {
    public:
        CpuBus(Ram *_ram);
        ~CpuBus();

        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t data);

    private:
        Ram *ram;
    };
};

#endif