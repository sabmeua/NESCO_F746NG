#include "Apu.h"

namespace nesco::core
{

    void Apu::writeRegister(uint16_t addr, uint8_t data)
    {
        uint16_t idx = addr % 0x4000;
        if (idx <= 0x17 && (idx != 0x14 || idx != 0x16)) {
            if (idx == 0x17) {
                data &= 0xC0;
            }
            Register.index[idx] = data;
        }
    }
    
    uint8_t Apu::readRegister(uint16_t addr)
    {
        uint8_t data = 0;
        uint16_t idx = addr % 0x4000;
        if (idx <= 0x17 && (idx != 0x14 || idx != 0x16)) {
            data = Register.index[idx];
        } else {
            // Abort
        }
        return data;
    }

};
