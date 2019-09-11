#ifndef NESCO_CONFIG_H
#define NESCO_CONFIG_H

/****************************
 * Select nesco platform 
 ***************************/
//#define NESCO_PLATFORM_GLUT
#define NESCO_PLATFORM_MBED

/**
 * Platform dependent provision
 */
#if defined NESCO_PLATFORM_GLUT

    #include "nesco/device/Glut.h"

#elif defined NESCO_PLATFORM_MBED

    #include "mbed.h"

    /**
     * Select mbed device 
     */
    #define NESCO_DEVICE_DISCOF746NG

    #if defined NESCO_DEVICE_DISCOF746NG
        #include "nesco/device/DiscoF746NG.h"
        typedef nesco::device::EmuDevice_DiscoF746NG NescoDevice;
    #endif

#endif

#endif
