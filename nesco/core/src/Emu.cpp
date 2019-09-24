#include "Emu.h"

namespace nesco::core
{
    Emu::Emu(EmuDevice &_dev) : dev(_dev)
    {
        ram = new Ram(0x800);
        ppubus = new PpuBus();
        ppu = new Ppu(ppubus);
        dma = new Dma(ram, ppu);
        apu = new Apu();
        cpubus = new CpuBus(ram, ppu, apu, dma);
        cpu = new Cpu(cpubus);
    }

    Emu::~Emu()
    {
        delete cpubus;
        delete cpu;
        delete ram;
        delete ppubus;
        delete ppu;
        delete dma;
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

    void Emu::loadCartridge(Cartridge *cartridge)
    {
        cpubus->loadCartridge(cartridge);
        ppubus->loadCartridge(cartridge);
    }
};