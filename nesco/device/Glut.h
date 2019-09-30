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
        void init();
        void redraw();
    protected:
        const int width = 256;
        const int height = 240;

        unsigned char image[240][256][3];
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
        void init();
        void reset();
        void main();

        void callEmuMain();
        void redraw();
    };
};

#endif
