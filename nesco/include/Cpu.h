#ifndef NESCO_CPU_H
#define NESCO_CPU_H

#include <cstdint>
#include "CpuBus.h"

namespace nesco
{
    /**
     * Memory map
     *
     * $0000 - $07FF	RAM 2Kbytes
     *   # $01A0-$01FF	Stack 96 bytes
     * $0800 - $1FFF	Unused (mirrored $0000-$07FF)
     * $2000 - $2007	I/O (PPU)
     * $2008 - $3FFF	Unused (mirrored $2000-$2007)
     * $4000 - $401F	I/O (APU, etc)
     * $4020 - $5FFF	Extented RAM (for specific mapper)
     * $6000 - $7FFF    Battery backuped NVRAM
     * $8000 - $BFFF	Program ROM-Low
     * $C000 - $FFFF	Program ROM-High
     *
     */
    #define RESET_VECTOR    0xFFFC
    #define NMI_VECTOR      0xFFFA
    #define IRQ_VECTOR      0xFFFE
    #define SP_BASE         0x00FD
    #define SP_OFFSET       0x0100  // Accessing stack as "SP | SP_OFFSET"

    enum CpuStatusFlag
    {
        CarryFlag    = 0x01,
        ZeroFlag     = 0x02,
        IrqFlag      = 0x04,
        DecimalFlag  = 0x08,
        BreakFlag    = 0x10,
        OverflowFlag = 0x40,
        NegativeFlag = 0x80,
    };
    #define INITIAL_STATUS 0x34

    /**
     * Addressing mode
     */
    enum AddressingMode
    {
        Immediate1 = 0x00,  // #$00 for Opcode Set 0x00 and 0x10 group
        IndirectX  = 0x00,  // ($00,X)
        Zeropage   = 0x04,  // $00
        Accumlator = 0x08,  // A << 1
        Immediate2 = 0x08,  // #$00 for Opcode Set 0x01 group
        Absolute   = 0x0C,  // $0000
        IndirectY  = 0x10,  // ($00),Y
        ZeropageX  = 0x14,  // $00,X
        ZeropageY  = 0x16,  // $00,Y
        AbsoluteY  = 0x18,  // $0000,Y
        AbsoluteX  = 0x1C,  // $0000,X
        Immediate,
        Indirect,           // ($0000) for JMP command
        Implied,            // implied in command
        Relative,           // PC relative
    };

    class Cpu
    {
    public:
        Cpu(CpuBus *_cpubus);
        ~Cpu();

        void reset();
        void step();

    private:
        // Registers
        uint8_t A;      // Accumlator
        uint8_t X;      // Index register 1
        uint8_t Y;      // Index register 2
        uint8_t SP;     // Stack pointer
        uint8_t P;      // Status register
                        // bit 0:C carry flag
                        //     1:Z zero flag
                        //     2:I IRQ flag
                        //     3:D decimal flag
                        //     4:B break flag
                        //     5:. reserved
                        //     6:V overflow flag
                        // bit 7:N negative flag
        uint16_t PC;    // Program counter

        CpuBus *bus;
        uint8_t skipCycle;

        bool execOpImplied(uint8_t opcode);
        bool execOpBranch(uint8_t opcode);
        bool execOp00(uint8_t opcode);
        bool execOp01(uint8_t opcode);
        bool execOp10(uint8_t opcode);

        // Stack operations
        void push(uint8_t value);
        uint8_t pop();
        void pushWord(uint16_t value);
        uint16_t popWord();

        // Read from PC
        uint8_t fetch();
        uint16_t fetchWord();

        // IO methods
        uint8_t read(uint16_t addr);
        uint16_t readWord(uint16_t addr, bool zp = false);
        void write(uint16_t addr, uint8_t data);

        // Status register operations
        void setFlag(CpuStatusFlag flag);
        void setFlag(CpuStatusFlag flag, uint8_t value);
        void setFlagNZ(uint8_t value);
        void clearFlag(CpuStatusFlag flag);
        bool getFlag(CpuStatusFlag flag);

        uint16_t loadAddr(AddressingMode mode);
        bool checkPageCross(uint16_t addr1, uint16_t addr2);
    };

};

#endif
