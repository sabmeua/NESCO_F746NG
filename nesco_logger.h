#ifndef NESCO_LOGGER_H
#define NESCO_LOGGER_H

#include "nesco_config.h"

#if defined NESCO_PLATFORM_GLUT
    #include "DefaultLogger.h"
    typedef DefaultLogger Logger;
#elif defined NESCO_PLATFORM_MBED
    #include "DefaultLogger.h"
    typedef DefaultLogger Logger;
#endif

#endif
