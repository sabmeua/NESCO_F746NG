#ifndef NESCO_EMU_DEVICE_DISCOF746NG_H
#define NESCO_EMU_DEVICE_DISCOF746NG_H

#include "EmuDevice.h"

namespace nesco::device
{
    class DiscoF746NG : public core::EmuDevice
    {
    public:
        void reset();
        void load(const char *path);
    };
};

#endif
