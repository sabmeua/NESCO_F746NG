#ifndef NESCO_ROM_H
#define NESCO_ROM_H

#include <cstdint>

namespace nesco::core
{
    class Rom
    {
    public:
        Rom(uint16_t size);
        ~Rom();
        uint8_t read(uint16_t addr);

    private:
        uint16_t size;
        uint8_t *mem;
    };
};

#endif