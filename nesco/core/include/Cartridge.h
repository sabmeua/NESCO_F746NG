#ifndef NESCO_CORE_CARTRIDGE_H
#define NESCO_CORE_CARTRIDGE_H

#include "EmuDevice.h"
#include "Rom.h"
#include "Mapper.h"

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

        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t data);

    private:
        EmuDevice &dev;
        uint8_t header[INES_HEADER_SIZE];

        Mapper *mapper;

        Rom *progRom;
        Rom *charRom;

        uint8_t progPageNum() { return header[4]; }
        uint8_t charPageNum() { return header[5]; }
    };
};

#endif
