#ifndef NESCO_HAL_DEFAULT_LOGGER_H
#define NESCO_HAL_DEFAULT_LOGGER_H

#include <cstdio>
#include <cstdarg>

namespace nesco::hal
{
    enum LogLevel {
        LogLvError,
        LogLvWarning,
        LogLvInfo,
        LogLvDebug
    };

    class DefaultLogger
    {
    public:
        static void puts(LogLevel lv, ...);

    protected:
        static const char * const logLvStr[];
        static char logLv;
        static const char *getTimestamp() {
            return "##";
        }
    };
};

#endif
