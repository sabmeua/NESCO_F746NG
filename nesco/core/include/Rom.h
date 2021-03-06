#ifndef NESCO_CORE_ROM_H
#define NESCO_CORE_ROM_H

#include <cstdint>

namespace nesco::core
{
    class Rom
    {
    public:
        Rom(uint16_t _size);
        Rom(uint16_t _size, uint8_t *_mem) : size(_size), mem(_mem) {}
        ~Rom();
        uint8_t read(uint16_t addr);

    private:
        uint16_t size;
        uint8_t *mem;
    };
};

#endif