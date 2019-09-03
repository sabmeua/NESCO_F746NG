#ifndef NESCO_PPU_H
#define NESCO_PPU_H

#include "PpuBus.h"

namespace nesco
{
    class Ppu
    {
    public:
        Ppu(PpuBus *_ppubus);
        ~Ppu();

        void reset();

    private:
        PpuBus *bus;
    };
};
#endif
