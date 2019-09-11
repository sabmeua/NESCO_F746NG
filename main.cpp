#include "nesco_config.h"
#include "Emu.h"

NescoDevice dev;

int main()
{
    nesco::core::Emu *emu = new nesco::core::Emu(dev);
    emu->run();
    return 0;
}
