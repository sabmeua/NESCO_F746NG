#include "Cpu.h"
#include "CpuOpcodes.h"
#include "nesco_logger.h"

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
        PC = readWord(RESET_VECTOR);
    }

    void Cpu::step(uint16_t clk)
    {
        if (skipCycle > 0) {
            skipCycle--;
            return;
        }

        uint8_t opcode = fetch();
        LOG_TRACE("<CPU> %5d: op=%02X | PC=%04X SP=%02X", clk / 3, opcode, PC-1, SP);

        if (execOpImplied(opcode) ||
            execOpBranch(opcode) ||
            execOp00(opcode) ||
            execOp01(opcode) ||
            execOp10(opcode) ||
            execOpUnofficial(opcode))
        {
            skipCycle += OpCycles[opcode];
        } else {
            Emu::abort("Invalid opcode");
        }
    }

    void Cpu::write(uint16_t addr, uint8_t data)
    {
        skipCycle += bus->write(addr, data);
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
                interrupt(IntBrk);
                break;
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
        OpcodeSet_00 comm = static_cast<OpcodeSet_00>(opcode & COMMAND_MASK);

        // Irregular pattern
        if (opcode == JMP_IND) {
            mode = Indirect;
        }

        switch (mode) {
            case Accumlator:
            case ZeropageY:
            case AbsoluteY:
            case IndirectX:
            case IndirectY:
                return false;
            case Immediate:
                if (comm == JMP || comm == STY) {
                    return false;
                }
                mode = Immediate;
                break;
            case Zeropage:
                if (comm == BIT || comm == JMP) {
                    return false;
                }
                break;
            case ZeropageX:
                if (comm != STY && comm == LDY) {
                    return false;
                }
                break;
            case AbsoluteX:
                if (comm != LDY) {
                    return false;
                }
                break;
            case Indirect:
                if (comm != JMP) {
                    return false;
                }
                break;
            default:
                break;
        }

        uint16_t addr = loadAddr(mode);

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
        OpcodeSet_01 comm = static_cast<OpcodeSet_01>(opcode & COMMAND_MASK);


        switch (mode) {
            case Accumlator:
            case ZeropageY:
            case Indirect:
                return false;
            case Immediate:
                if (comm == STA) {
                    return false;
                }
                break;
            default:
                break;
        }

        uint16_t addr = loadAddr(mode);

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
            case OP_ADC:
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
        OpcodeSet_10 comm = static_cast<OpcodeSet_10>(opcode & COMMAND_MASK);

        // irregular pattern
        if (opcode == LDX_ABS_Y) {
            mode = AbsoluteY;
        } else if (opcode == STX_ZPG_Y) {
            mode = ZeropageY;
        }

        switch (mode) {
            case Indirect:
            case IndirectX:
            case IndirectY:
                return false;
            case Accumlator:
                if (comm == STX || comm == LDX || comm == DEC || comm == INC) {
                    return false;
                }
                break;
            case Immediate:
                if (comm != LDX) {
                    return false;
                }
                break;
            case AbsoluteX:
            case ZeropageX:
                if (comm == STX || comm == LDX) {
                    return false;
                }
                break;
            case ZeropageY:
                if (comm != STX && comm != LDX) {
                    return false;
                }
                break;
            case AbsoluteY:
                if (comm != LDX && comm != DEC && comm != INC) {
                    return false;
                }
                break;
            default:
                break;
        }

        uint16_t addr = loadAddr(mode);

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

    bool Cpu::execOpUnofficial(uint8_t opcode)
    {
        // @ToDo: Implement unofficial opcodes
        // @See: http://www.oxyron.de/html/opcodes02.html
        switch (opcode) {
            // SLO {adr}:={adr}*2 A:=A or {adr}
            case 0x07:  // Immediate
            case 0x17:  // Zeropage
            case 0x03:  // ZeropageY
            case 0x13:  // IndirectX
            case 0x0F:  // IndirectY
            case 0x1F:  // Absolute
            case 0x1B:  // AbsoluteX
                break;
            // RLA {adr}:={adr}rol A:=A and {adr}
            case 0x27:  // Immediate
            case 0x37:  // Zeropage
            case 0x23:  // ZeropageY
            case 0x33:  // IndirectX
            case 0x2F:  // IndirectY
            case 0x3F:  // Absolute
            case 0x3B:  // AbsoluteX
                break;
            // SRE {adr}:={adr}/2 A:=A exor {adr}
            case 0x47:  // Immediate
            case 0x57:  // Zeropage
            case 0x43:  // ZeropageY
            case 0x53:  // IndirectX
            case 0x4F:  // IndirectY
            case 0x5F:  // Absolute
            case 0x5B:  // AbsoluteX
                break;
            // RRA {adr}:={adr}ror A:=A adc {adr}
            case 0x67:  // Immediate
            case 0x77:  // Zeropage
            case 0x63:  // ZeropageY
            case 0x73:  // IndirectX
            case 0x6F:  // IndirectY
            case 0x7F:  // Absolute
            case 0x7B:  // AbsoluteX
                break;
            // SAX A,X:={adr}
            case 0x87:  // Immediate
            case 0x97:  // ZeropageX
            case 0x83:  // ZeropageY
            case 0x8F:  // IndirectY
                break;
            // LAX A,X:={adr}
            case 0xA7:  // Immediate
            case 0xB7:  // ZeropageX
            case 0xA3:  // ZeropageY
            case 0xB3:  // IndirectX
            case 0xAF:  // IndirectY
            case 0xBF:  // AbsoluteX
                break;
            // DCP {adr}:={adr}-1 A-{adr}
            case 0xC7:  // Immediate
            case 0xD7:  // Zeropage
            case 0xC3:  // ZeropageY
            case 0xD3:  // IndirectX
            case 0xCF:  // IndirectY
            case 0xDF:  // Absolute
            case 0xDB:  // AbsoluteX
                break;
            // ISC {adr}:={adr}+1 A:=A-{adr}
            case 0xE7:  // Immediate
            case 0xF7:  // Zeropage
            case 0xE3:  // ZeropageY
            case 0xF3:  // IndirectX
            case 0xEF:  // IndirectY
            case 0xFF:  // Absolute
            case 0xFB:  // AbsoluteX
                break;
            // ANC A:=A&#{imm}
            case 0x0B:  // Immediate
            case 0x2B:  // Immediate
                break;
            // ALR A:=(A&#{imm})/2
            case 0x4B:  // Implied
                break;
            // ARR A:=(A&#{imm})/2
            case 0x6B:  // Implied
                break;
            // XAA A:=X&#{imm}
            case 0x8B:  // Immediate
                break;
            // LAX A,X:=#{imm}
            case 0xAB:  // Immediate
                break;
            // AXS X:=A&X-#{imm}
            case 0xCB:  // Implied
                break;
            // SBC A:=A-#{imm}
            case 0xEB:  // Implied
                break;
            // AHX {adr}:=A&X&H
            case 0x93:  // IndirectY
            case 0x9F:  // AbsoluteY
            // SHY {adr}:=Y&H
            case 0x9C:  // AbsoluteX
                break;
            // SHX {adr}:=X&H
            case 0x9E:  // AbsoluteY
                break;
            // TAS S:=A&X {adr}:=S&H
            case 0x9B:  // AbsoluteY
                break;
            // LAS A,X,S:={adr}&S
            case 0xBB:  // AbsoluteX
                break;
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

    void Cpu::interrupt(CpuIntType type)
    {
        uint16_t vector = type == IntNmi ? NMI_VECTOR : IRQ_VECTOR;

        if (type != IntNmi && getFlag(IrqFlag)) {
            return;
        }

        if (type == IntBrk) {
            setFlag(BreakFlag);
            PC++;
        } else {
            clearFlag(BreakFlag);
        }

        pushWord(PC);
        push(P);

        setFlag(IrqFlag);

        PC = readWord(vector);
    }

    void Cpu::nmi()
    {
        interrupt(IntNmi);
        skipCycle += 7;
    }

    void Cpu::irq()
    {
        interrupt(IntIrq);
        skipCycle += 7;
    }
};
