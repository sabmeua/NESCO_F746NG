#ifndef NESCO_CARTRIDGE_H
#define NESCO_CARTRIDGE_H

#include <cstdint>
#include "EmuDevice.h"

namespace nesco::core
{
    class Cartridge
    {
    public:
        static Cartridge *load(EmuDevice *dev, const char *path)
        {
            dev->load(path);
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
