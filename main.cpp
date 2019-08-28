#include "mbed.h"
#include "Emu.h"

int main()
{
    Emu *emu = new Emu();
    emu->run();
    return 0;
}