#ifndef NESCO_EMU_H
#define NESCO_EMU_H

#include "Cpu.h"
#include "Ppu.h"
#include "Ram.h"
#include "CpuBus.h"
#include "EmuDevice.h"

namespace nesco
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
        CpuBus *cpubus;
        Ram *ram;
    };
};

#endif