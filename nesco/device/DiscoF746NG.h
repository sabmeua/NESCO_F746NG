#ifndef NESCO_EMU_DEVICE_DISCOF746NG_H
#define NESCO_EMU_DEVICE_DISCOF746NG_H

#include "mbed.h"
#include "BlockDevice.h"
#include "EmuDevice.h"

#define NESCO_DEBUG
#ifdef NESCO_DEBUG
    #include "FATFileSystem.h"
#else
    #include "LittleFileSystem.h"
#endif

namespace nesco::device
{
#ifdef NESCO_DEBUG
    typedef FATFileSystem NescoFileSystem;
#else
    typedef LittleFileSystem NescoFileSystem;
#endif

    class DiscoF746NG : public core::EmuDevice
    {
    public:
        void reset();
        FILE *load(const char *path);
    private:
        FILE *cartridgeFile;
    };
};

#endif
