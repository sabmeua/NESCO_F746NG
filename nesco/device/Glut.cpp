#include "nesco/device/Glut.h"

extern nesco::device::Glut dev;

namespace nesco::device
{
    void draw()
    {
    }

    void input(unsigned char code, int x, int y)
    {
    }

    void idle()
    {
        dev.callEmuMain();
    }

    Glut::Glut()
    {
        display = new DisplayGlut();
        filesystem = new DefaultFilesystem();
        sound = new SoundGlut();
        keypad = new KeypadGlut();
    }

    void Glut::main()
    {
        int *argc;
        char **argv;

        glutInit(argc, argv);
        glutInitWindowSize(256, 240);
        glutInitDisplayMode(GLUT_RGBA);
        glutCreateWindow("nesco");
        glutDisplayFunc(draw);
        glPixelZoom(1, -1);
        glutKeyboardFunc(input);
        glClearColor(1, 1, 1, 1);
        glutIdleFunc(idle);
        //glutTimerFunc(1, timer, 0);
        glutMainLoop();
    }

    void Glut::callEmuMain()
    {
        callback[EmuMain]();   
    }
};
