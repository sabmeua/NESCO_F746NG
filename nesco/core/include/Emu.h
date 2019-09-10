#ifndef NESCO_EMU_H
#define NESCO_EMU_H

#include "Cpu.h"
#include "Ppu.h"
#include "Apu.h"
#include "Ram.h"
#include "CpuBus.h"
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

    private:
        EmuDevice &dev;

        Cpu *cpu;
        Ppu *ppu;
        Apu *apu;
        CpuBus *cpubus;
        PpuBus *ppubus;
        Ram *ram;
    };
};

#endif