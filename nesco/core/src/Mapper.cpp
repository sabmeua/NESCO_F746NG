#include "Mapper.h"

namespace nesco::core
{
    uint8_t Mapper0::read(uint16_t addr)
    {
        if (addr < 0x2000) {
            return cartridge->charRom->read(addr);
        } else if (addr >= 0x8000 && addr <= 0xFFFF) {
            addr %= 0x8000;
            if (cartridge->progPageNum() == 1) {
                addr %= INES_PROG_PAGE_SIZE;
            }
            return cartridge->progRom->read(addr);
        }
        return 0;
    }

    void Mapper0::write(uint16_t addr, uint8_t data)
    {
        // Nop
    }
};
