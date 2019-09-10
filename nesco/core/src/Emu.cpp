#include "Emu.h"

namespace nesco::core
{
    Emu::Emu(EmuDevice &_dev) : dev(_dev)
    {
        ram = new Ram(0x800);
        ppubus = new PpuBus();
        ppu = new Ppu(ppubus);
        apu = new Apu();
        cpubus = new CpuBus(ram, ppu, apu);
        cpu = new Cpu(cpubus);
    }

    Emu::~Emu()
    {
        delete cpubus;
        delete cpu;
        delete ram;
        delete ppubus;
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