#include "mbed.h"
#include "Emu.h"

using namespace nesco;

int main()
{
    Emu *emu = new Emu();
    emu->run();
    return 0;
}