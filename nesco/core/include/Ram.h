#ifndef NESCO_RAM_H
#define NESCO_RAM_H

#include <cstdint>

namespace nesco
{
    class Ram
    {
    public:
        Ram(uint16_t size);
        ~Ram();
        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t data);
        void reset();

    private:
        uint16_t size;
        uint8_t *mem;
    };
};

#endif