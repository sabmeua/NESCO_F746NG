#include "Cartridge.h"

namespace nesco::core
{
    Cartridge::~Cartridge()
    {
        if (progRom) {
            delete progRom;
        }
        if (charRom) {
            delete charRom;
        }
    }
    
    bool Cartridge::parse(const char *path)
    {
        hal::NescoFileHandle h = dev.filesystem->open(path, "r");

        dev.filesystem->read(h, header, INES_HEADER_SIZE);

        // Check "NES\1A" magic number
        if (header[0] != 'N' || header[1] != 'E' || header[2] != 'S' || header[3] != 0x1A) {
            return false;
        }

        // Check size of Program ROM
        uint8_t progPageNum = header[4];
        if (progPageNum == 0) {
            return false;
        }
        progRom = new uint8_t[INES_PROG_PAGE_SIZE * progPageNum];
        dev.filesystem->read(h, progRom, INES_PROG_PAGE_SIZE * progPageNum);

        // Check size of Character ROM
        uint8_t charPageNum = header[5];
        if (charPageNum > 0) {
            charRom = new uint8_t[INES_CHAR_PAGE_SIZE * charPageNum];
            dev.filesystem->read(h, charRom, INES_CHAR_PAGE_SIZE * charPageNum);
        }

        // Check TV system is NTSC
        if ((header[10] & 0x03) != 0) {
            return false;
        }

        // Check extram support
        if (header[6] & 0x02) {
            return false;
        }

        // Check mapper number
        mapperNo = ((header[6] & 0xF0) >> 4) | (header[7] & 0xF0);

        dev.filesystem->close(h);

        return true;
    }
};
