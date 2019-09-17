#ifndef NESCO_EMU_DEVICE_GLUT_H
#define NESCO_EMU_DEVICE_GLUT_H

#include "EmuDevice.h"

namespace nesco::device
{
    class EmuDevice_Glut : public core::EmuDevice
    {
    public:
        void reset();
        void load(const char *path);
    };
};

#endif
