#ifndef NESCO_HAL_DEFAULT_FILESYSTEM_H
#define NESCO_HAL_DEFAULT_FILESYSTEM_H

#include <string>
#include <cstdint>
#include <fstream>

#include "hal/include/FilesystemHal.h"

namespace nesco::hal
{
    class DefaultFilesystem : public FilesystemHal
    {
    public:
        void init();
        NescoFileHandle open(const char *key, const char *mode);
        bool read(NescoFileHandle h, uint8_t *buff, uint32_t size);
        bool write(NescoFileHandle h, uint8_t *buff, uint32_t size);
        bool seek(NescoFileHandle h, uint32_t offset, uint8_t origin);
        bool readLine(NescoFileHandle h, char *buff);
        bool writeLine(NescoFileHandle h, const char *buff);
        void close(NescoFileHandle h);
    };
};

#endif
