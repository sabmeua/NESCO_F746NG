#ifndef NESCO_CORE_MAPPER_H
#define NESCO_CORE_MAPPER_H

#include "Cartridge.h"

namespace nesco::core
{
    class Cartridge;

    class Mapper
    {
    public:
        virtual uint8_t read(uint16_t addr) = 0;
        virtual void write(uint16_t addr, uint8_t data) = 0;
    };

    class Mapper0 : public Mapper
    {
    public:
        Mapper0(Cartridge *cart) : cartridge(cart) {}
        virtual uint8_t read(uint16_t addr);
        virtual void write(uint16_t addr, uint8_t data);
    private:
        Cartridge *cartridge;
    };
};

#endif
