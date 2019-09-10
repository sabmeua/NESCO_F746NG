#include "Dma.h"

namespace nesco::core
{
    Dma::Dma(Ram *_ram, Ppu *_ppu)
        : ram(_ram), ppu(_ppu)
    {
    }
};
