#ifndef NESCO_EMU_DEVICE_DISCOF746NG_H
#define NESCO_EMU_DEVICE_DISCOF746NG_H

#include "EmuDevice.h"
#include "MbedFilesystem.h"

using namespace nesco::core;
using namespace nesco::hal;

namespace nesco::device
{
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
