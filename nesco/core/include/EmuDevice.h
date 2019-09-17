#ifndef NESCO_EMU_DEVICE_H
#define NESCO_EMU_DEVICE_H

#include <fstream>

namespace nesco::core
{
    class EmuDevice {
    public:
        virtual void reset() = 0;
        virtual std::ifstream &load(const char *path) = 0;
    };

};

#endif
