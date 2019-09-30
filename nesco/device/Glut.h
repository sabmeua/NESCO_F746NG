#ifndef NESCO_DEVICE_GLUT_H
#define NESCO_DEVICE_GLUT_H

#include <GL/glut.h>
#include "EmuDevice.h"
#include "DefaultFilesystem.h"

using namespace nesco::core;
using namespace nesco::hal;

namespace nesco::device
{
    class DisplayGlut : public DisplayHal
    {
    public:
        void init() {}
    };

    class SoundGlut : public SoundHal
    {
    public:
        void init() {}
    };

    class KeypadGlut : public KeypadHal
    {
    public:
        void init() {}
    };

    class Glut : public EmuDevice
    {
    public:
        Glut();
        void main();
        void callEmuMain();
    };
};

#endif
