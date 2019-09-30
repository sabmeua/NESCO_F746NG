#include "nesco/device/Glut.h"
#include "nesco_logger.h"

extern nesco::device::Glut dev;
unsigned char image[240][256][3];

namespace nesco::device
{
    void draw()
    {
        dev.redraw();
    }

    void input(unsigned char code, int x, int y)
    {
        switch(code) {
            case 0x1b:
                LOG_INFO("Normaly exit");
                exit(0);
            case ',':
                LOG_TRACE("Press B");
                break;
            case '.':
                LOG_TRACE("Press A");
                break;
            case 'w':
                LOG_TRACE("Press Up");
                break;
            case 'a':
                LOG_TRACE("Press Left");
                break;
            case 's':
                LOG_TRACE("Press Down");
                break;
            case 'd':
                LOG_TRACE("Press Right");
                break;
            case '@':
                LOG_TRACE("Press Start");
                break;
            case '[':
                LOG_TRACE("Press Select");
                break;
            default:
                break;
        }
    }

    void tick()
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
#if 1
        glutIdleFunc(tick);
#else
        glutTimerFunc(6, tick, 0);
#endif
        glutMainLoop();
    }

    void Glut::callEmuMain()
    {
        callback[EmuMain]();
    }

    void Glut::redraw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawPixels(256, 240, GL_RGB, GL_UNSIGNED_BYTE, image);
        glFlush();
    }
};
