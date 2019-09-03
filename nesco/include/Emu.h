#ifndef NESCO_EMU_H
#define NESCO_EMU_H

#include "Cpu.h"
#include "Ppu.h"
#include "Ram.h"
#include "CpuBus.h"

namespace nesco
{
    class Emu
    {
    public:
        Emu();
        ~Emu();
    
        void run();
        void reset();

    private:
        Cpu *cpu;
        Ppu *ppu;
        CpuBus *cpubus;
        Ram *ram;
    };
};

#endif