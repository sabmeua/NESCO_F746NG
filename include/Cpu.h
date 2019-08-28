#ifndef NESCO_CPU_H
#define NESCO_CPU_H

#include <cstdint>

class Cpu
{
public:
    Cpu();
    ~Cpu();

private:
    // Registers
    uint8_t A;
    uint8_t X;
    uint8_t Y;
    uint8_t SP;
    uint16_t PC;

    uint8_t flags;
};

#endif