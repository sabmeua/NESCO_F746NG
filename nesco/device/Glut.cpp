#include "nesco/device/Glut.h"

namespace nesco::device
{
    Glut::Glut()
    {
        display = new DisplayGlut();
        filesystem = new DefaultFilesystem();
        sound = new SoundGlut();
        keypad = new KeypadGlut();
    }
};
