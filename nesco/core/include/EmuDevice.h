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
    enum EmuCallbackType {
        EmuMainLoop = 0,
        EmuCallbackTypeNum,
    };

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

        void setCallback(EmuCallbackType type, std::function<void(void)> _func) {
            callback[type] = _func;
        }

        void main() {
            while(true) {
                callback[EmuMainLoop]();
            }
        }
    protected:
        std::function<void(void)> callback[EmuCallbackTypeNum];
    };

};

#endif
