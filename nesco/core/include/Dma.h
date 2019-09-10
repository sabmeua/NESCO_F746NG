#ifndef NESCO_DMA_H
#define NESCO_DMA_H

#include "Ram.h"
#include "Ppu.h"

namespace nesco::core
{
    class Dma
    {
    public:
        Dma(Ram *ram, Ppu *ppu);
        
    private:
        Ram *ram;
        Ppu *ppu;
    };
};

#endif
