#ifndef NESCO_CPU_H
#define NESCO_CPU_H

#include <cstdint>
#include "Ram.h"

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

    class Cpu
    {
    public:
        Cpu(Ram *_ram);
        ~Cpu();

        void reset();
        void exec();
        uint8_t fetch();

        // Stack operations
        void push(uint8_t value);
        uint8_t pop();

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

        Ram *ram;
        uint8_t skipCycle;
    };
};

#endif