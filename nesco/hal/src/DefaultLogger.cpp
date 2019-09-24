#include "nesco/hal/include/DefaultLogger.h"

namespace nesco::hal
{
    const char * const DefaultLogger::logLvStr[] = {
        "FATAL",
        "ERROR",
        "WARNING",
        "INFO",
        "DEBUG",
        "TRACE"
    };

    char DefaultLogger::logLv = LogLvDebug;

    void DefaultLogger::puts(LogLevel lv, ...)
    {
        if (lv > logLv) {
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
