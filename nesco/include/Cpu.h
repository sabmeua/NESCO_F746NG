#ifndef NESCO_CPU_H
#define NESCO_CPU_H

#include <cstdint>
#include "CpuBus.h"

namespace nesco
{
    /**
     * Memory map
     *
     * $0000 - $07FF	RAM
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

    enum StatusFlag
    {
        CarryFlag    = 0x01,
        ZeroFlag     = 0x02,
        IrqFlag      = 0x04,
        DecimalFlag  = 0x08,
        BreakFlag    = 0x10,
        OverflowFlag = 0x40,
        NegativeFlag = 0x80,
    };

    class Cpu
    {
    public:
        Cpu(CpuBus *_bus);
        ~Cpu();

        void reset();
        void exec();

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
        uint8_t exCycle;

        bool execOpImplied(uint8_t opcode);
        bool execOpBranch(uint8_t opcode);
        bool execOpOthers(uint8_t opcode);
        bool execOp00(uint8_t opcode);
        bool execOp01(uint8_t opcode);
        bool execOp10(uint8_t opcode);

        // Stack operations
        void push(uint8_t value);
        uint8_t pop();
        void pushWord(uint16_t value);
        uint16_t popWord();

        uint8_t fetch();
        uint8_t read(uint16_t addr);
        uint16_t readWord(uint16_t addr);
        void write(uint16_t addr, uint8_t data);

        void setFlag(StatusFlag flag);
        void setFlag(StatusFlag flag, uint8_t value);
        void setFlagNZ(uint8_t value);
        void clearFlag(StatusFlag flag);
    };

};

#endif
