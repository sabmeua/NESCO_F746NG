#ifndef NESCO_HAL_DISPLAY_H
#define NESCO_HAL_DISPLAY_H

namespace nesco::hal
{
    class DisplayHal
    {
    public:
        virtual void init() = 0;
    };
};

#endif
