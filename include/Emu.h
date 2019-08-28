#ifndef NESCO_EMU_H
#define NESCO_EMU_H

#include "Cpu.h"
#include "Ram.h"

class Emu
{
public:
    Emu();
    ~Emu();
    
    void run();
    void reset();

private:
    Cpu *cpu;
    Ram *ram;
};

#endif