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
        static void puts(LogLevel lv, ...) {
            if (lv < logLv) {
                return;
            }
            printf("%s [%s] ", getTimestamp(), logLvStr[lv]);
            va_list vargs;
            va_start(vargs, lv);
            char *msg = va_arg(vargs, char *);
            vprintf(msg, vargs);
            va_end(vargs);
            printf("\n");
        }

    protected:
        static const char * const logLvStr[];
        static char logLv;
        static const char *getTimestamp() {
            return "##";
        }
    };
};

#endif
