#ifndef NESCO_CORE_EMU_DEVICE_H
#define NESCO_CORE_EMU_DEVICE_H

#include <functional>

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

        void setCallback(std::function<void(void)> _func) {
            mainloop = _func;
        }

        void main() {
            int i = 0;
            while(i++ < 100) {
                mainloop();
            }
        }
    protected:
        std::function<void(void)> mainloop;
    };

};

#endif
