#ifndef NESCO_HAL_LOGGER_H
#define NESCO_HAL_LOGGER_H

namespace nesco::hal
{
    enum LogLevel {
        LogLvError,
        LogLvWarning,
        LogLvInfo,
        LogLvDebug
    };

    class LoggerHal
    {
    public:
        static void puts(LogLevel lv, ...) {}

    protected:
        static const char * const logLvStr[];
        static char logLv;
        static const char *getTimestamp() {
            return "##";
        }
    };

    const char * const LoggerHal::logLvStr[] = {
        "ERROR",
        "WARNING",
        "INFO",
        "DEBUG"
    };

    char LoggerHal::logLv = LogLvDebug;

    #define LOG_ERROR(...) Logger::puts(LogLvError, __VA_ARGS__)
    #define LOG_WARNING(...) Logger::puts(LogLvWarning, __VA_ARGS__)
    #define LOG_INFO(...) Logger::puts(LogLvInfo, __VA_ARGS__)
    #define LOG_DEBUG(...) Logger::puts(LogLvDebug, __VA_ARGS__)
};

#endif
