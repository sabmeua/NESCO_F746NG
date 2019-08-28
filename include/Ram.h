#ifndef NESCO_RAM_H
#define NESCO_RAM_H

#include <cstdint>

#define RAM_SIZE 0x800

class Ram
{
public:
    Ram();
    ~Ram();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);
    void reset();

private:
    uint8_t mem[RAM_SIZE];
};

#endif