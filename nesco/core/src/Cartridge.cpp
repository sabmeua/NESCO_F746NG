#include "Cartridge.h"

namespace nesco::core
{
    Cartridge::~Cartridge()
    {
        delete progRom;
        delete charRom;
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
        uint8_t *prom = new uint8_t[INES_PROG_PAGE_SIZE * progPageNum];
        dev.filesystem->read(h, prom, INES_PROG_PAGE_SIZE * progPageNum);
        progRom = new Rom(INES_PROG_PAGE_SIZE * progPageNum, prom);

        // Check size of Character ROM
        uint8_t charPageNum = header[5];
        if (charPageNum > 0) {
            uint8_t *crom = new uint8_t[INES_CHAR_PAGE_SIZE * charPageNum];
            dev.filesystem->read(h, crom, INES_CHAR_PAGE_SIZE * charPageNum);
            charRom = new Rom(INES_CHAR_PAGE_SIZE * charPageNum, crom);
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
        uint8_t mapperNo = ((header[6] & 0xF0) >> 4) | (header[7] & 0xF0);
        mapper = new Mapper0();

        dev.filesystem->close(h);

        return true;
    }

    uint8_t Cartridge::read(uint16_t addr)
    {
        return mapper->read(addr);
    }

    void Cartridge::write(uint16_t addr, uint8_t data)
    {
        mapper->write(addr, data);
    }

};
