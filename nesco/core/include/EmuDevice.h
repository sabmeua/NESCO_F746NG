#ifndef NESCO_EMU_DEVICE_H
#define NESCO_EMU_DEVICE_H

#include "hal/include/Display.h"
#include "hal/include/Sound.h"
#include "hal/include/Filesystem.h"
#include "hal/include/Keypad.h"

namespace nesco::core
{
    class EmuDevice :
        public hal::DisplayHal,
        public hal::SoundHal,
        public hal::FilesystemHal,
        public hal::KeypadHal
    {
    public:
        virtual void reset() = 0;
    };

};

#endif
