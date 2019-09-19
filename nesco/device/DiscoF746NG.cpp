#include "nesco/device/DiscoF746NG.h"

namespace nesco::device
{
    DiscoF746NG::DiscoF746NG()
    {
        display = new DisplayDiscoF746NG();
        filesystem = new MbedFilesystem();
        sound = new SoundDiscoF746NG();
        keypad = new KeypadDiscoF746NG();
    }
};
