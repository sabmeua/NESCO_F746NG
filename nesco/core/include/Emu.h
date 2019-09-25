#ifndef NESCO_CORE_EMU_H
#define NESCO_CORE_EMU_H

#include <cstdint>

#include "Cpu.h"
#include "Ppu.h"
#include "Apu.h"
#include "Ram.h"
#include "CpuBus.h"
#include "Cartridge.h"
#include "EmuDevice.h"

namespace nesco::core
{
    class Emu
    {
    public:
        Emu(EmuDevice &_dev);
        ~Emu();
    
        void run();
        void reset();
        void loadCartridge(Cartridge *catridge);

    private:
        uint16_t clk;
        EmuDevice &dev;

        Cpu *cpu;
        Ppu *ppu;
        Apu *apu;
        CpuBus *cpubus;
        PpuBus *ppubus;
        Ram *ram;
        Dma *dma;
    };
};

#endif