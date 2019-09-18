#ifndef NESCO_EMU_DEVICE_DISCOF746NG_H
#define NESCO_EMU_DEVICE_DISCOF746NG_H

#include "mbed.h"
#include "BlockDevice.h"
#include "EmuDevice.h"

namespace nesco::device {};

#define NESCO_DEBUG
#ifdef NESCO_DEBUG
    #include "FATFileSystem.h"
    typedef FATFileSystem NescoFileSystem;
#else
    #include "LittleFileSystem.h"
    typedef LittleFileSystem NescoFileSystem;
#endif

namespace nesco::device
{
    class DiscoF746NG : public core::EmuDevice
    {
    public:
        void reset();
        FILE *load(const char *path);
    private:
        FILE *cartridgefp;
    };
};

#endif
