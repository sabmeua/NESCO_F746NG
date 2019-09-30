#include "nesco_config.h"
#include "nesco_logger.h"
#include "Emu.h"

NescoDevice dev;

using namespace nesco::core;

int main()
{
    Logger::setLogLevel(LogLvTrace);
    LOG_DEBUG("Start NESCO ******************");
    dev.init();
    Emu *emu = new Emu(dev);
    Cartridge *cart = new Cartridge(dev);
    cart->parse("sample/helloworld.nes");
    emu->loadCartridge(cart);
    emu->run();
    LOG_DEBUG("Stop NESCO *******************");
    return 0;
}
