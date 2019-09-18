#ifndef NESCO_EMU_DEVICE_H
#define NESCO_EMU_DEVICE_H

#include "hal/include/Display.h"
#include "hal/include/Sound.h"
#include "hal/include/Filesystem.h"
#include "hal/include/Keypad.h"

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
