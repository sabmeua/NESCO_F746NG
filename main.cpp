#include "nesco_config.h"
#include "nesco_logger.h"
#include "Emu.h"

NescoDevice dev;

using namespace nesco::core;

int main()
{
    LOG_DEBUG("Start NESCO ******************");
    Emu *emu = new Emu(dev);
    Cartridge *cart = new Cartridge(dev);
    cart->parse("sample/helloworld.nes");
    emu->loadCartridge(cart);
    emu->reset();
    emu->run();
    LOG_DEBUG("Stop NESCO *******************");
    return 0;
}
