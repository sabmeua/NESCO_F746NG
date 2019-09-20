#ifndef NESCO_HAL_DEFAULT_LOGGER_H
#define NESCO_HAL_DEFAULT_LOGGER_H

#include <cstdio>
#include <cstdarg>

#include "nesco/hal/include/LoggerHal.h"

namespace nesco::hal
{
    class DefaultLogger : public LoggerHal
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
    };
};

#endif
