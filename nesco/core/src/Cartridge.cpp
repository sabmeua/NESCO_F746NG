#include "Cartridge.h"
#include "nesco_logger.h"

namespace nesco::core
{
    Cartridge::~Cartridge()
    {
        delete progRom;
        delete charRom;
    }
    
    bool Cartridge::loadInes(EmuDevice &dev, const char *path)
    {
        LOG_INFO("load cartridge file : %s", path);

        hal::NescoFileHandle h = dev.filesystem->open(path, "r");

        dev.filesystem->read(h, header, INES_HEADER_SIZE);

        // Check "NES\1A" magic number
        if (header[0] != 'N' || header[1] != 'E' || header[2] != 'S' || header[3] != 0x1A) {
            LOG_ERROR("Invalid iNES magic number");
            return false;
        }

        // Check size of Program ROM
        uint8_t progPageNum = header[4];
        if (progPageNum == 0) {
            LOG_ERROR("No program ROM bank assigned");
            return false;
        }
        LOG_INFO("## program ROM page size = %d", progPageNum);
        
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
        LOG_INFO("## character ROM page size = %d", charPageNum);

        // Check TV system is NTSC
        if ((header[10] & 0x03) != 0) {
            LOG_ERROR("PAL cartridge is not supported");
            return false;
        }

        // Check extram support
        if (header[6] & 0x02) {
            LOG_ERROR("Extra RAM is not supported");
            return false;
        }

        // Check mapper number
        uint8_t mapperNo = ((header[6] & 0xF0) >> 4) | (header[7] & 0xF0);
        LOG_INFO("## mapper No. = %d", mapperNo);

        mapper = new Mapper0(this);

        LOG_INFO("## name table mirroring mode = %d", mirroingMode());

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
