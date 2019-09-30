#include "Emu.h"
#include "nesco_logger.h"

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

        dev.setCallback(EmuMainLoop, [&](void) {
            if (clk % 3 == 0) {
                cpu->step(clk);
            }
            ppu->step(clk);
            if (++clk == 0xFFFF) {
                clk = 0;
            }
        });
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
        dev.main();
    }

    void Emu::reset()
    {
        clk = 0;
        dev.reset();
        cpu->reset();
        ppu->reset();
    }

    void Emu::loadCartridge(Cartridge *cartridge)
    {
        cpubus->loadCartridge(cartridge);
        ppubus->loadCartridge(cartridge);
    }

    void Emu::abort(const char *err)
    {
        LOG_FATAL(err);
        // @ToDo: abort process
        exit(1);
    }
};