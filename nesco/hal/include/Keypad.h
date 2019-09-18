#ifndef NESCO_HAL_KEYPAD_H
#define NESCO_HAL_KEYPAD_H

namespace nesco::hal
{
    class KeypadHal
    {
    public:
        virtual void init() = 0;
    };
};

#endif
