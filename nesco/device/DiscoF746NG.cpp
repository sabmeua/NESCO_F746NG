#include "mbed.h"
#include "nesco/device/DiscoF746NG.h"

namespace nesco::device
{
    class Display_DiscoF746NG : public hal::DisplayHal
    {
    } disp746ng;

    class Sound_DiscoF746NG : public hal::SoundHal
    {
    } sound746ng;

    class Filesystem_DiscoF746NG : public hal::FilesystemHal
    {
    } fs746ng;

    class Keypad_DiscoF746NG : public hal::KeypadHal
    {
    } keypad746ng;

    void DiscoF746NG::reset()
    {
    }
};
