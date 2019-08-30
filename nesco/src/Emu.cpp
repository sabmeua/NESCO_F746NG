#include "Emu.h"

namespace nesco
{
    Emu::Emu()
    {
        ram = new Ram();
        cpubus = new CpuBus(ram);
        cpu = new Cpu(cpubus);
    }

    Emu::~Emu()
    {
        delete cpubus;
        delete cpu;
        delete ram;
    }

    void Emu::run()
    {
    }

    void Emu::reset()
    {
    }
};