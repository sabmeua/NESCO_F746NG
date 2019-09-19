#include "nesco_config.h"
#include "Emu.h"

NescoDevice dev;

using namespace nesco::core;

int main()
{
    Emu *emu = new Emu(dev);
    Cartridge *cart = new Cartridge(dev);
    cart->parse("sample/helloworld.nes");
    emu->load(cart);
    emu->reset();
    emu->run();
    return 0;
}
