#ifndef NESCO_HAL_MBED_FILESYSTEM_H
#define NESCO_HAL_MBED_FILESYSTEM_H

#include "nesco/hal/include/FilesystemHal.h"

#include "mbed.h"
#include "BlockDevice.h"

#define NESCO_DEBUG
#ifdef NESCO_DEBUG
    #include "FATFileSystem.h"
    typedef FATFileSystem RealFileSystem;
#else
    #include "LittleFileSystem.h"
    typedef LittleFileSystem RealFileSystem;
#endif

namespace nesco::hal
{
    class MbedFilesystem : public FilesystemHal
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
