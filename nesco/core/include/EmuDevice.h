#ifndef NESCO_CORE_EMU_DEVICE_H
#define NESCO_CORE_EMU_DEVICE_H

#include "hal/include/DisplayHal.h"
#include "hal/include/SoundHal.h"
#include "hal/include/FilesystemHal.h"
#include "hal/include/KeypadHal.h"

using namespace nesco::hal;

namespace nesco::core
{
    class EmuDevice
    {
    public:
        void reset() {
            display->init();
            sound->init();
            filesystem->init();
            keypad->init();
        };

        DisplayHal *display;
        SoundHal *sound;
        FilesystemHal *filesystem;
        KeypadHal *keypad;
    };

};

#endif
