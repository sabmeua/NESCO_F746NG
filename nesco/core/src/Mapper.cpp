#include "Mapper.h"

namespace nesco::core
{
    uint8_t Mapper0::read(uint16_t addr)
    {
        return cartridge->progRom->read(addr);
    }

    void Mapper0::write(uint16_t addr, uint8_t data)
    {
    }
};
