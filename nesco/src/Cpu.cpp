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

    uint16_t Cpu::readWord(uint16_t addr, bool zp)
    {
        uint16_t mask = zp ? 0x00FF : 0xFFFF;
        return read((addr & mask)) | (read((addr + 1) & mask) << 8);
    }

    void Cpu::push(uint8_t value)
    {
        write(0x100 | SP--, value);
    }

    uint8_t Cpu::pop()
    {
        return read(0x100 | ++SP);
    }

    void Cpu::pushWord(uint16_t value)
    {
        push((value >> 8) & 0xFF);
        push(value & 0xFF);
    }

    uint16_t Cpu::popWord()
    {
        return pop() | (pop() << 8);
    }

    uint8_t Cpu::fetch()
    {
        return read(PC++);
    }

    uint16_t Cpu::fetchWord()
    {
        return fetch() | (fetch() << 8);
    }

    void Cpu::setFlag(StatusFlag flag)
    {
        P |= flag;
    }

    void Cpu::clearFlag(StatusFlag flag)
    {
        P &= ~flag;
    }

    void Cpu::setFlag(StatusFlag flag, bool value)
    {
        P = (flag * static_cast<uint8_t>(value)) | (~flag | P);
    }

    void Cpu::setFlagNZ(uint8_t value)
    {
        setFlag(NegativeFlag, value & NegativeFlag);
        setFlag(ZeroFlag, value == 0);
    }

    bool Cpu::getFlag(StatusFlag flag)
    {
        return P & flag;
    }

    bool Cpu::execOpImplied(uint8_t opcode)
    {
        switch (static_cast<OpcodeSet_Implied>(opcode)) {
            case BRK:
            {
                bool interrupt = P & IrqFlag;
                PC++;
                pushWord(PC);
                setFlag(BreakFlag);
                push(P);
                setFlag(IrqFlag);
                if (!interrupt) {
                    PC = readWord(0xFFFE);
                }
                PC--;
                break;
            }
            case PHP:
                push(P);
                break;
            case CLC:
                clearFlag(CarryFlag);
                break;
            case JSR:
            {
                uint16_t addr = fetchWord();
                pushWord(PC - 1);
                PC = addr;
                break;
            }
            case PLP:
                P = pop();
                break;
            case SEC:
                setFlag(CarryFlag);
                break;
            case RTI:
                P = pop();
                PC = popWord();
                break;
            case PHA:
                push(A);
                break;
            case CLI:
                clearFlag(IrqFlag);
                break;
            case RTS:
                PC = popWord();
                PC++;
                break;
            case PLA:
                A = pop();
                setFlagNZ(A);
                break;
            case SEI:
                setFlag(IrqFlag);
                break;
            case DEY:
                Y = (Y - 1) & 0xFF;
                setFlagNZ(Y);
                break;
            case TXA:
                A = X;
                setFlagNZ(A);
                break;
            case TYA:
                A = Y;
                setFlagNZ(Y);
                break;
            case TXS:
                SP = X;
                break;
            case TAY:
                Y = A;
                setFlagNZ(Y);
                break;
            case TAX:
                X = A;
                setFlagNZ(X);
                break;
            case CLV:
                clearFlag(OverflowFlag);
                break;
            case TSX:
                X = SP;
                setFlagNZ(X);
                break;
            case INY:
                Y = (Y + 1) & 0xFF;
                setFlagNZ(Y);
                break;
            case DEX:
                X = (X - 1) & 0xFF;
                setFlagNZ(X);
                break;
            case CLD:
                clearFlag(DecimalFlag);
                break;
            case INX:
                X = (X + 1) & 0xFF;
                setFlagNZ(X);
                break;
            case NOP:
                break;
            case SED:
                setFlag(DecimalFlag);
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
        if ((opcode & OPCODE_SET_MASK) != 0) {
            return false;
        }

        AddressingMode mode = static_cast<AddressingMode>(opcode & ADDR_MODE_MASK);
        uint16_t addr;
        // Irregular pattern
        if (opcode == JMP_IND) {
            mode = Indirect;
        }
        switch (mode) {
            case Immediate:
                addr = PC++;
                break;
            case Zeropage:
                addr = fetch() & 0xFF;
                break;
            case ZeropageX:
                addr = (fetch() + X) & 0xFF;
                break;
            case Absolute:
                addr = fetchWord();
                break;
            case AbsoluteX:
                addr = fetchWord() + X;
                break;
            case Indirect:
                addr = fetchWord();
                addr = readWord(addr);
                break;
            default:
                return false;
        }

        OpcodeSet_00 comm = static_cast<OpcodeSet_00>(opcode & COMMAND_MASK);
        switch (comm) {
            case BIT:
            {
                uint8_t data = read(addr);
                setFlag(ZeroFlag, !(A & data) * ZeroFlag);
                setFlag(OverflowFlag, data);
                setFlag(NegativeFlag, data);
                break;
            }
            case JMP:
                PC = addr;
                break;
            case STY:
                write(addr, Y);
                break;
            case LDY:
                Y = read(addr);
                setFlagNZ(Y);
                break;
            case CPY:
            {
                uint16_t cmp = Y - read(addr);
                setFlag(CarryFlag, (cmp > 0) * CarryFlag);
                setFlagNZ(cmp);
                break;
            }
            case CPX:
            {
                uint16_t cmp = X - read(addr);
                setFlag(CarryFlag, (cmp > 0) * CarryFlag);
                setFlagNZ(cmp);
                break;
            }
            default:
                return false;
        }

        return true;
    }

    bool Cpu::execOp01(uint8_t opcode)
    {
        if ((opcode & OPCODE_SET_MASK) != 1) {
            return false;
        }

        AddressingMode mode = static_cast<AddressingMode>(opcode & ADDR_MODE_MASK);
        uint16_t addr;
        switch (mode) {
            case Immediate2:
                addr = PC++;
                break;
            case Zeropage:
                addr = fetch() & 0xFF;
                break;
            case ZeropageX:
                addr = (fetch() + X) & 0xFF;
                break;
            case Absolute:
                addr = fetchWord();
                break;
            case AbsoluteX:
                addr = fetchWord() + X;
                break;
            case AbsoluteY:
                addr = fetchWord() + Y;
                break;
            case IndirectX:
                addr = (fetch() + X) & 0xFF;
                addr = readWord(addr, true);
                break;
            case IndirectY:
                addr = fetch();
                addr = readWord(addr, true) + Y;
                break;
            default:
                return false;
        }

        OpcodeSet_01 comm = static_cast<OpcodeSet_01>(opcode & COMMAND_MASK);
        switch (comm) {
            case ORA:
                A |= read(addr);
                setFlagNZ(A);
                break;
            case AND:
                A &= read(addr);
                setFlagNZ(A);
                break;
            case EOR:
                A ^= read(addr);
                setFlagNZ(A);
                break;
            case ADC:
            {
                uint8_t data = read(addr);
                uint16_t sum = A + data + getFlag(CarryFlag);
                setFlag(CarryFlag, (sum & 0x0100) >> 8);
                setFlag(OverflowFlag, (A ^ sum) & (data ^ sum) & 0xFF);
                A = sum & 0xFF;
                setFlagNZ(A);
                break;
            }
            case STA:
                write(addr, A);
                break;
            case LDA:
                A = read(addr);
                setFlagNZ(A);
                break;
            case CMP:
            {
                uint16_t cmp = A - read(addr);
                setFlag(CarryFlag,  (!(cmp & 0x0100) >> 8));
                setFlagNZ(cmp & 0xFF);
                break;
            }
            case SBC:
            {
                uint16_t data = read(addr);
                uint16_t sub = A - data - !getFlag(CarryFlag);
                setFlag(CarryFlag, !(sub & 0x0100) >> 8);
                setFlag(OverflowFlag, (A ^ sub) & (~data ^ sub) & 0x80);
                A = sub;
                setFlagNZ(A);
                break;
            }
            default:
                return false;
        }

        return true;
    }    

    bool Cpu::execOp10(uint8_t opcode)
    {
        if ((opcode & OPCODE_SET_MASK) != 2) {
            return false;
        }

        AddressingMode mode = static_cast<AddressingMode>(opcode & ADDR_MODE_MASK);
        uint16_t addr;
        // irregular pattern
        if (opcode == LDX_ABS_Y) {
            mode = AbsoluteY;
        } else if (opcode == STX_ZPG_Y) {
            mode = ZeropageY;
        }
        switch (mode) {
            case Accumlator:
                break;
            case Immediate:
                addr = PC++;
                break;
            case Zeropage:
                addr = fetch() & 0xFF;
                break;
            case ZeropageX:
                addr = (fetch() + X) & 0xFF;
                break;
            case ZeropageY:
                addr = (fetch() + Y) & 0xFF;
                break;
            case Absolute:
                addr = fetchWord();
                break;
            case AbsoluteX:
                addr = fetchWord() + X;
                break;
            case AbsoluteY:
                addr = fetchWord() + Y;
                break;
            default:
                return false;
        }

        OpcodeSet_10 comm = static_cast<OpcodeSet_10>(opcode & COMMAND_MASK);
        switch (comm) {
            case ASL:
            case ROL:
            {
                uint8_t carry = 0;
                if (comm == ROL) {
                    carry = (P & CarryFlag) / CarryFlag;
                }
                if (mode == Accumlator) {
                    setFlag(CarryFlag, A & 0x80);
                    A = A << 1 | carry;
                    setFlagNZ(A);
                } else {
                    uint8_t data = read(addr);
                    setFlag(CarryFlag, data & 0x80);
                    data = data << 1 | carry;
                    write(addr, data);
                    setFlagNZ(data);
                }
                break;
            }
            case LSR:
            case ROR:
            {
                uint8_t carry = 0;
                if (comm == ROR) {
                    carry = ((P & CarryFlag) / CarryFlag) << 7;
                }
                if (mode == Accumlator) {
                    setFlag(CarryFlag, A & 0x01);
                    A = A >> 1 | carry;
                    setFlagNZ(A);
                } else {
                    uint8_t data = read(addr);
                    setFlag(CarryFlag, data & 0x01);
                    data = data >> 1 | carry;
                    write(addr, data);
                    setFlagNZ(data);
                }
                break;
            }
            case STX:
                write(addr, X);
                break;
            case LDX:
                X = read(addr);
                setFlagNZ(X);
                break;
            case DEC:
            {
                uint8_t data = read(addr) - 1;
                setFlagNZ(data);
                write(addr, data);
                break;
            }
            case INC:
            {
                uint8_t data = read(addr) + 1;
                setFlagNZ(data);
                write(addr, data);
                break;
            }
            default:
                return false;
        }

        return true;
    }

};
