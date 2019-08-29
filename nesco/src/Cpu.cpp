#include "Cpu.h"
#include "CpuOpcodes.h"

namespace nesco
{
    Cpu::Cpu(Ram *_ram)
    {
        ram = ram;
        skipCycle = 0;
    }

    Cpu::~Cpu()
    {
    }

    void Cpu::reset()
    {
    }

    void Cpu::exec()
    {
        if (skipCycle-- > 0) {
            return;
        }

        uint8_t opcode = fetch();
        if (true/* exec command here */) {
            skipCycle = OpCycles[opcode];
        }

        ++PC;
    }

    void Cpu::push(uint8_t value)
    {
        ram->write(0x100 | SP, value);
        --SP;
    }

    uint8_t Cpu::pop()
    {
        ++SP;
        return ram->read(0x100 | SP);
    }

    uint8_t Cpu::fetch()
    {
        return ram->read(PC);
    }
};