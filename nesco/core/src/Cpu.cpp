#include "Cpu.h"
#include "CpuOpcodes.h"

namespace nesco::core
{
    Cpu::Cpu(CpuBus *_cpubus) : bus(_cpubus)
    {
        skipCycle = 0;
    }

    Cpu::~Cpu()
    {
    }

    void Cpu::reset()
    {
        skipCycle = 0;
        A = X = Y = 0;
        P = INITIAL_STATUS;
        SP = SP_BASE;
        PC = RESET_VECTOR;
    }

    void Cpu::step()
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
            skipCycle += OpCycles[opcode];
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
        write(SP_OFFSET | SP--, value);
    }

    uint8_t Cpu::pop()
    {
        return read(SP_OFFSET | ++SP);
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

    void Cpu::setFlag(CpuStatusFlag flag)
    {
        P |= flag;
    }

    void Cpu::clearFlag(CpuStatusFlag flag)
    {
        P &= ~flag;
    }

    void Cpu::setFlag(CpuStatusFlag flag, uint8_t value)
    {
        P = (flag & value) | (~flag | P);
    }

    void Cpu::setFlagNZ(uint8_t value)
    {
        setFlag(NegativeFlag, value);
        setFlag(ZeroFlag, (value == 0) * ZeroFlag);
    }

    bool Cpu::getFlag(CpuStatusFlag flag)
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
                    PC = readWord(IRQ_VECTOR);
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

        uint16_t addr = loadAddr(Relative);

        if (branch) {
            PC = addr;
            skipCycle += 1;
        } else {
            PC++;
        }

        return true;
    }

    bool Cpu::execOp00(uint8_t opcode)
    {
        if ((opcode & OPCODE_SET_MASK) != 0) {
            return false;
        }

        AddressingMode mode = static_cast<AddressingMode>(opcode & ADDR_MODE_MASK);
        if (mode == Immediate1) {
            mode = Immediate;
        }

        // Irregular pattern
        if (opcode == JMP_IND) {
            mode = Indirect;
        }
        uint16_t addr = loadAddr(mode);

        OpcodeSet_00 comm = static_cast<OpcodeSet_00>(opcode & COMMAND_MASK);
        switch (comm) {
            case BIT:
            {
                uint8_t data = read(addr);
                setFlag(ZeroFlag, ((A & data) > 0) * ZeroFlag);
                setFlag(NegativeFlag, data);
                setFlag(OverflowFlag, data);
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
                setFlagNZ(cmp & 0xFF);
                break;
            }
            case CPX:
            {
                uint16_t cmp = X - read(addr);
                setFlag(CarryFlag, (cmp > 0) * CarryFlag);
                setFlagNZ(cmp & 0xFF);
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
        if (mode == Immediate2) {
            mode = Immediate;
        }

        uint16_t addr = loadAddr(mode);

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
                setFlag(OverflowFlag, ~(A ^ data) & (A ^ sum));
                A = sum & 0xFF;
                setFlag(CarryFlag, (sum >> 8) * CarryFlag);
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
                setFlag(CarryFlag,  !(cmp >> 8) * CarryFlag);
                setFlagNZ(cmp & 0xFF);
                break;
            }
            case SBC:
            {
                uint8_t data = read(addr) ^ 0xFF;
                uint16_t sum = A + data + getFlag(CarryFlag);
                setFlag(OverflowFlag, ~(A ^ data) & (A ^ sum));
                A = sum & 0xFF;
                setFlag(CarryFlag, (sum >> 8) * CarryFlag);
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
        if (mode == Immediate1) {
            mode = Immediate;
        }

        // irregular pattern
        if (opcode == LDX_ABS_Y) {
            mode = AbsoluteY;
        } else if (opcode == STX_ZPG_Y) {
            mode = ZeropageY;
        }

        uint16_t addr = loadAddr(mode);

        OpcodeSet_10 comm = static_cast<OpcodeSet_10>(opcode & COMMAND_MASK);
        switch (comm) {
            case ASL:
            case ROL:
            {
                uint8_t carry = 0;
                if (comm == ROL) {
                    carry = getFlag(CarryFlag);
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
                    carry = getFlag(CarryFlag) << 7;
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

    uint16_t Cpu::loadAddr(AddressingMode mode)
    {
        uint16_t addr = 0;

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
            case ZeropageY:
                addr = (fetch() + Y) & 0xFF;
                break;
            case Absolute:
                addr = fetchWord();
                break;
            case AbsoluteX:
            {
                uint16_t base = fetchWord();
                skipCycle += checkPageCross(base, base + X);
                addr = base + X;
                break;
            }
            case AbsoluteY:
            {
                uint16_t base = fetchWord();
                skipCycle += checkPageCross(base, base + Y);
                addr = base + Y;
                break;
            }
            case Indirect:
                addr = fetchWord();
                addr = readWord(addr);
                break;
            case IndirectX:
                addr = (fetch() + X) & 0xFF;
                addr = readWord(addr, true);
                break;
            case IndirectY:
            {
                uint16_t base = readWord(fetch(), true);
                skipCycle += checkPageCross(base, base + Y);
                addr = base + Y;
                break;
            }
            case Relative:
            {
                uint16_t offset = fetch();
                addr = PC + offset;
                skipCycle += checkPageCross(PC, addr);
                break;
            }
            default:
                break;
        }

        return addr;
    }

    bool Cpu::checkPageCross(uint16_t addr1, uint16_t addr2)
    {
        return (addr1 & 0xFF00) != (addr2 & 0xFF00);
    }
};
