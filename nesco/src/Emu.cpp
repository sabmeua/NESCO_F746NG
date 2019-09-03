#include "Emu.h"

namespace nesco
{
    Emu::Emu()
    {
        ram = new Ram();
        cpubus = new CpuBus(ram);
        cpu = new Cpu(cpubus);
        ppu = new Ppu();
    }

    Emu::~Emu()
    {
        delete cpubus;
        delete cpu;
        delete ram;
    }

    void Emu::run()
    {
        reset();
    }

    void Emu::reset()
    {
        cpu->reset();
        ppu->reset();
    }
};