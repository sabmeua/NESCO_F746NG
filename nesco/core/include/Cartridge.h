#ifndef NESCO_CARTRIDGE_H
#define NESCO_CARTRIDGE_H

#include <EmuDevice.h>

namespace nesco::core
{
    #define INES_HEADER_SIZE 16
    #define INES_PROG_PAGE_SIZE 0x4000  // 16KB
    #define INES_CHAR_PAGE_SIZE 0x2000  // 8KB

    class Cartridge
    {
    public:
        bool parse(const char *path);

        Cartridge(EmuDevice &_dev) : dev(_dev) {}
        ~Cartridge();

        uint8_t mirroingMode() { return header[6] & 0x01; }

    private:
        EmuDevice &dev;
        uint8_t header[INES_HEADER_SIZE];
        uint8_t *progRom;
        uint8_t *charRom;
        uint8_t mapperNo;

        uint8_t progPageNum() { return header[4]; }
        uint8_t charPageNum() { return header[5]; }
    };
};

#endif
