#include "Rom.h"

namespace nesco::core
{
    Rom::Rom(uint16_t _size) : size(_size)
    {
        mem = new uint8_t[size];
    }

    Rom::~Rom()
    {
        delete mem;
    }

    uint8_t Rom::read(uint16_t addr)
    {
        return mem[addr % size];
    }
};