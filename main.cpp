#include "mbed.h"
#include "Emu.h"
#include "nesco/device/DiscoF746NG.h"

using namespace nesco;

device::EmuDevice_DiscoF746NG emu746ng;

int main()
{
    Emu *emu = new Emu(emu746ng);
    emu->run();
    return 0;
}
