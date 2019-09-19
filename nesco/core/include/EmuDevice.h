#ifndef NESCO_EMU_DEVICE_H
#define NESCO_EMU_DEVICE_H

#include "hal/include/DisplayHal.h"
#include "hal/include/SoundHal.h"
#include "hal/include/FilesystemHal.h"
#include "hal/include/KeypadHal.h"
#include "hal/include/LoggerHal.h"

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
        LoggerHal *logger;
    };

};

#endif
