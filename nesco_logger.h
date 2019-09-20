#ifndef NESCO_LOGGER_H
#define NESCO_LOGGER_H

#include "nesco_config.h"

//#define LOG_DISABLE

#ifndef LOG_DISABLE

    #if defined NESCO_PLATFORM_GLUT
        #include "DefaultLogger.h"
        typedef DefaultLogger Logger;
    #elif defined NESCO_PLATFORM_MBED
        #include "DefaultLogger.h"
        typedef DefaultLogger Logger;
    #endif

    #define LOG_ERROR(...) Logger::puts(LogLvError, __VA_ARGS__)
    #define LOG_WARNING(...) Logger::puts(LogLvWarning, __VA_ARGS__)
    #define LOG_INFO(...) Logger::puts(LogLvInfo, __VA_ARGS__)
    #define LOG_DEBUG(...) Logger::puts(LogLvDebug, __VA_ARGS__)

#else

    #define LOG_ERROR(...)
    #define LOG_WARNING(...)
    #define LOG_INFO(...)
    #define LOG_DEBUG(...)

#endif

#endif
