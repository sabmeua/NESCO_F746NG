#include "Cpu.h"
#include "CpuOpcodes.h"

namespace nesco
{
    Cpu::Cpu(CpuBus *_bus)
    {
        bus = bus;
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

        exCycle = 0;
        uint8_t opcode = fetch();

        if (execOpImplied(opcode) ||
            execOpBranch(opcode) ||
            execOp00(opcode) ||
            execOp01(opcode) ||
            execOp10(opcode))
        {
            skipCycle += OpCycles[opcode] + exCycle;
        } else {
            // implement! abort & logging
        }
    }

    void Cpu::write(uint16_t addr, uint8_t data)
    {
        bus->write(addr, data);
    }

    uint8_t Cpu::read(uint16_t addr)
    {
        return bus->read(addr);
    }

    void Cpu::push(uint8_t value)
    {
        write(0x100 | SP--, value);
    }

    uint8_t Cpu::pop()
    {
        return read(0x100 | ++SP);
    }

    uint8_t Cpu::fetch()
    {
        return read(PC++);
    }

    bool Cpu::execOpImplied(uint8_t opcode)
    {
        switch (static_cast<OpcodeSet_Implied>(opcode)) {
            case BRK:
                break;
            case PHP:
                break;
            case CLC:
                break;
            case JSR:
                break;
            case PLP:
                break;
            case SEC:
                break;
            case RTI:
                break;
            case PHA:
                break;
            case CLI:
                break;
            case RTS:
                break;
            case PLA:
                break;
            case SEI:
                break;
            case DEY:
                break;
            case TXA:
                break;
            case TYA:
                break;
            case TXS:
                break;
            case TAY:
                break;
            case TAX:
                break;
            case CLV:
                break;
            case TSX:
                break;
            case INY:
                break;
            case DEX:
                break;
            case CLD:
                break;
            case INX:
                break;
            case NOP:
                break;
            case SED:
                break;
            default:
                return false;
        }

        return true;
    }

    bool Cpu::execOpBranch(uint8_t opcode)
    {
        bool branch = false;
        uint16_t addr;

        switch (static_cast<OpcodeSet_Branch>(opcode)) {
            case BPL:
                branch = P & NegativeFlag;
                break;
            case BMI:
                branch = ~P & NegativeFlag;
                break;
            case BVC:
                branch = P & OverflowFlag;
                break;
            case BVS:
                branch = ~P & OverflowFlag;
                break;
            case BCC:
                branch = P & CarryFlag;
                break;
            case BCS:
                branch = ~P & CarryFlag;
                break;
            case BNE:
                branch = P & ZeroFlag;
                break;
            case BEQ:
                branch = ~P & ZeroFlag;
                break;
            default:
                return false;
        }

        addr = 0x0000; /** @ToDo: read addr from ram by realative mode */

        if (branch) {
            PC = addr;
            exCycle += 1;
        }

        return true;
    }

    bool Cpu::execOp00(uint8_t opcode)
    {
        if ((opcode & 0x3) != 0) {
            return false;
        }

        AddressingMode mode = static_cast<AddressingMode>(opcode & 0x1C);
        switch (static_cast<OpcodeSet_00>(opcode & 0xE0)) {
            case BIT:
                break;
            case JMP:
                break;
            case STY:
                break;
            case LDY:
                break;
            case CPY:
                break;
            case CPX:
                break;
            default:
                return false;
        }

        return true;
    }

    bool Cpu::execOp01(uint8_t opcode)
    {
        if ((opcode & 0x3) != 1) {
            return false;
        }

        AddressingMode mode = static_cast<AddressingMode>(opcode & 0x1C);
        switch (static_cast<OpcodeSet_01>(opcode & 0xE0)) {
            case ORA:
                break;
            case AND:
                break;
            case EOR:
                break;
            case ADC:
                break;
            case STA:
                break;
            case LDA:
                break;
            case CMP:
                break;
            case SBC:
                break;
            default:
                return false;
        }

        return true;
    }    

    bool Cpu::execOp10(uint8_t opcode)
    {
        if ((opcode & 0x3) != 2) {
            return false;
        }

        AddressingMode mode = static_cast<AddressingMode>(opcode & 0x1C);
        switch (static_cast<OpcodeSet_10>(opcode & 0xE0)) {
            case ASL:
                break;
            case ROL:
                break;
            case LSR:
                break;
            case ROR:
                break;
            case STX:
                break;
            case LDX:
                break;
            case DEC:
                break;
            case INC:
                break;
            default:
                return false;
        }

        return true;
    }

};
