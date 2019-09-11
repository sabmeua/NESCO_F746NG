#include <GL/glut.h>
#include "nesco/device/Glut.h"

namespace nesco::device
{
    class Display_Glut : public hal::DisplayHal
    {
    } dispglut;

    class Sound_Glut : public hal::SoundHal
    {
    } soundglut;

    class Filesystem_Glut : public hal::FilesystemHal
    {
    } fsglut;

    class Keypad_Glut : public hal::KeypadHal
    {
    } keypadglut;

    void EmuDevice_Glut::reset()
    {
    }
};
