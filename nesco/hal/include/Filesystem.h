#ifndef NESCO_HAL_FILESYSTEM_H
#define NESCO_HAL_FILESYSTEM_H

#include <cstdint>

namespace nesco::hal
{
    typedef void* NescoFileHandle;

    class FilesystemHal
    {
    public:
        virtual void init() = 0;

        virtual NescoFileHandle open(const char *key, const char *mode) = 0;
        virtual bool read(NescoFileHandle h, uint8_t *buff, uint32_t size) = 0;
        virtual bool write(NescoFileHandle h, uint8_t *buff, uint32_t size) = 0;
        virtual bool seek(NescoFileHandle h, uint32_t offset, uint8_t origin) = 0;
        virtual bool readLine(NescoFileHandle h, uint8_t *buff) = 0;
        virtual bool writeLine(NescoFileHandle h, uint8_t *buff) = 0;
        virtual void close(NescoFileHandle h) = 0;
    };
};

#endif
