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

    void DiscoF746NG::reset()
    {
    }

    void DiscoF746NG::init()
    {
    }

    void DiscoF746NG::main()
    {
    }
};
