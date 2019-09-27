#include "nesco_config.h"
#include "nesco_logger.h"
#include "Emu.h"

NescoDevice dev;

using namespace nesco::core;

int main()
{
    dev.reset();
    Logger::setLogLevel(LogLvTrace);
    LOG_DEBUG("Start NESCO ******************");
    Emu *emu = new Emu();
    Cartridge *cart = new Cartridge();
    cart->loadInes(dev, "sample/helloworld.nes");
    emu->loadCartridge(cart);
    emu->run();
    LOG_DEBUG("Stop NESCO *******************");
    return 0;
}
