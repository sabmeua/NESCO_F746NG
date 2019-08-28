#include "Emu.h"

Emu::Emu()
{
    ram = new Ram();
    cpu = new Cpu(ram);
}

Emu::~Emu()
{
    delete cpu;
    delete ram;
}

void Emu::run()
{
}

void Emu::reset()
{
}