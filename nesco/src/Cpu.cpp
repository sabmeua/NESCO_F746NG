#include "Cpu.h"
#include "CpuOpcodes.h"

namespace nesco
{
    Cpu::Cpu(Ram *_ram)
    {
        ram = ram;
    }

    Cpu::~Cpu()
    {
    }

    void Cpu::reset()
    {
    }

    void Cpu::exec()
    {
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
};