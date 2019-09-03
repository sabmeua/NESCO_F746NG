#include "Emu.h"

namespace nesco
{
    Emu::Emu(EmuDevice &_dev) : dev(_dev)
    {
        ram = new Ram(0x800);
        cpubus = new CpuBus(ram);
        cpu = new Cpu(cpubus);
        ppu = new Ppu();
    }

    Emu::~Emu()
    {
        delete cpubus;
        delete cpu;
        delete ram;
        delete ppu;
    }

    void Emu::run()
    {
        reset();
    }

    void Emu::reset()
    {
        dev.reset();
        cpu->reset();
        ppu->reset();
    }
};