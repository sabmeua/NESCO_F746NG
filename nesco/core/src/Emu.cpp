#include "Emu.h"

namespace nesco
{
    Emu::Emu(EmuDevice &_dev) : dev(_dev)
    {
        ram = new Ram(0x800);
        charmem = new Ram(0x4000);
        ppubus = new PpuBus(charmem);
        ppu = new Ppu(ppubus);
        cpubus = new CpuBus(ram, ppu);
        cpu = new Cpu(cpubus);
    }

    Emu::~Emu()
    {
        delete cpubus;
        delete cpu;
        delete ram;
        delete ppubus;
        delete ppu;
        delete charmem;
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