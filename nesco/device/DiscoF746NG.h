#ifndef NESCO_EMU_DEVICE_DISCOF746NG_H
#define NESCO_EMU_DEVICE_DISCOF746NG_H

#include <fstream>

#include "mbed.h"
#include "FATFileSystem.h"
#include "BlockDevice.h"
#include "EmuDevice.h"

using namespace std;

namespace nesco::device
{
    class DiscoF746NG : public core::EmuDevice
    {
    public:
        void reset();
        ifstream &load(const char *path);
    private:
        ifstream cartridgeFile;
    };
};

#endif
