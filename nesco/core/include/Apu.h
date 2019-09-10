#ifndef NESCO_APU_H
#define NESCO_APU_H

#include <cstdint>

namespace nesco::core
{
    class Apu
    {
    public:
        void writeRegister(uint16_t addr, uint8_t data);
        uint8_t readRegister(uint16_t addr);
    };
};
#endif
