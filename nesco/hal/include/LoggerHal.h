#ifndef NESCO_HAL_LOGGER_H
#define NESCO_HAL_LOGGER_H

namespace nesco::hal
{
    class LoggerHal
    {
    public:
        virtual void init() = 0;
    };
};

#endif
