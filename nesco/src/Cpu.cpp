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

        if (execOpImplied(opcode) ||
            execOpBranch(opcode) ||
            execOp00(opcode) ||
            execOp01(opcode) ||
            execOp10(opcode))
        {
            skipCycle = OpCycles[opcode];
        } else {
            // implement! abort & logging
        }

        PC += 1;
    }

    void Cpu::push(uint8_t value)
    {
        ram->write(0x100 | SP--, value);
    }

    uint8_t Cpu::pop()
    {
        return ram->read(0x100 | ++SP);
    }

    uint8_t Cpu::fetch()
    {
        return ram->read(PC);
    }

    bool Cpu::execOpImplied(uint8_t opcode)
    {
        return false;
    }

    bool Cpu::execOpBranch(uint8_t opcode)
    {
        return false;
    }

    bool Cpu::execOp00(uint8_t opcode)
    {
        return false;
    }

    bool Cpu::execOp01(uint8_t opcode)
    {
        return false;
    }    

    bool Cpu::execOp10(uint8_t opcode)
    {
        return false;
    }
};