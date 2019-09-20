#include "nesco/hal/include/DefaultLogger.h"

namespace nesco::hal
{
    const char * const DefaultLogger::logLvStr[] = {
        "ERROR",
        "WARNING",
        "INFO",
        "DEBUG"
    };

    char DefaultLogger::logLv = LogLvDebug;
}