#ifndef NESCO_CORE_PPU_BUS_H
#define NESCO_CORE_PPU_BUS_H

#include "Ram.h"
#include "Cartridge.h"

namespace nesco::core
{
    class PpuBus
    {
    public:
        PpuBus();

        void loadCartridge(Cartridge *_cartridge) {
            cartridge = _cartridge;
        }

    private:
        Cartridge *cartridge;
    };
};

#endif
