#ifndef NESCO_CARTRIDGE_H
#define NESCO_CARTRIDGE_H

#include <vector>
#include <EmuDevice.h>

using namespace std;

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
        vector<uint8_t> progRom;
        vector<uint8_t> charRom;
        uint8_t mapperNo;
    };
};

#endif
