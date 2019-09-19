#ifndef NESCO_HAL_SOUND_H
#define NESCO_HAL_SOUND_H

namespace nesco::hal
{
    class SoundHal
    {
    public:
        virtual void init() = 0;
    };
};

#endif