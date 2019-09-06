#include "Ram.h"

namespace nesco
{
    Ram::Ram(uint16_t _size) : size(_size)
    {
        mem = new uint8_t[size];
    }

    Ram::~Ram()
    {
        delete mem;
    }

    uint8_t Ram::read(uint16_t addr)
    {
        return mem[addr % size];
    }

    void Ram::write(uint16_t addr, uint8_t data)
    {
        mem[addr % size] = data;
    }

    void Ram::reset()
    {
    }
};