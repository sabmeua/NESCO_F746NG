#ifndef NESCO_CARTRIDGE_H
#define NESCO_CARTRIDGE_H

#include <EmuDevice.h>

namespace nesco::core
{
    class Cartridge
    {
    public:
        static Cartridge *load(EmuDevice *dev, const char *path)
        {
            hal::NescoFileHandle fp = dev->filesystem->open(path, "r");
            return new Cartridge();
        };

        Cartridge();
        ~Cartridge();

    private:
        uint8_t *progRom;
        uint8_t *charRom;
        uint8_t mapperNo;
    };
};

#endif
