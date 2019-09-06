#ifndef NESCO_PPU_BUS_H
#define NESCO_PPU_BUS_H

#include "Ram.h"

namespace nesco::core
{
    class PpuBus
    {
    public:
        PpuBus(Ram *_charmem);

    private:
        Ram *charmem;
    };
};

#endif
