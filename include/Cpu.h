#ifndef NESCO_CPU_H
#define NESCO_CPU_H

#include <cstdint>
#include "Ram.h"

class Cpu
{
public:
    Cpu(Ram *_ram);
    ~Cpu();

    void reset();
    void exec();

    // Stack operations
    void push(uint8_t value);
    uint8_t pop();

private:
    // Registers
    uint8_t A;
    uint8_t X;
    uint8_t Y;
    uint8_t SP;
    uint16_t PC;

    uint8_t flags;
    Ram *ram;
};

#endif