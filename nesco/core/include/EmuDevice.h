#ifndef NESCO_EMU_DEVICE_H
#define NESCO_EMU_DEVICE_H

#include <stdio.h>

namespace nesco::core
{
    class EmuDevice {
    public:
        virtual void reset() = 0;
        virtual FILE *load(const char *path) = 0;
    };

};

#endif
