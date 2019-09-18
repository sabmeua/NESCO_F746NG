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

using namespace nesco::core;
using namespace nesco::hal;

namespace nesco::device
{
    class FilesystemDiscoF746NG : public FilesystemHal
    {
    public:
        void init();
        NescoFileHandle open(const char *key, const char *mode);
        bool read(NescoFileHandle h, uint8_t *buff, unsigned int size) {
            return true;
        }
        bool write(NescoFileHandle h, uint8_t *buff, unsigned int size) {
            return true;
        }
        bool seek(NescoFileHandle h, uint32_t offset, uint8_t origin) {
            return true;
        }
        bool readLine(NescoFileHandle h, uint8_t *buff) {
            return true;
        }
        bool writeLine(NescoFileHandle h, uint8_t *buff) {
            return true;
        }
        void close(NescoFileHandle h) {}
    };

    class DisplayDiscoF746NG : public DisplayHal
    {
    public:
        void init() {}
    };

    class SoundDiscoF746NG : public SoundHal
    {
    public:
        void init() {}
    };

    class KeypadDiscoF746NG : public KeypadHal
    {
    public:
        void init() {}
    };

    class DiscoF746NG : public EmuDevice
    {
    public:
        DiscoF746NG();
    };
};

#endif
