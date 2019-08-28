#include "Ram.h"

#define RAM_SIZE_MASK 0x7FF

Ram::Ram()
{
}

Ram::~Ram()
{
}

uint8_t Ram::read(uint16_t addr)
{
    return mem[addr & RAM_SIZE_MASK];
}

void Ram::write(uint16_t addr, uint8_t data)
{
    mem[addr & RAM_SIZE_MASK] = data;
}

void Ram::reset()
{
}