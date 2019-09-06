#ifndef NESCO_EMU_DEVICE_H
#define NESCO_EMU_DEVICE_H

namespace nesco::core
{
    class EmuDevice
    {
    public:
        virtual void reset() = 0;
    };

};

#endif
