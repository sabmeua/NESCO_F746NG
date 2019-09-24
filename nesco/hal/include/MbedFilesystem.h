#ifndef NESCO_HAL_MBED_FILESYSTEM_H
#define NESCO_HAL_MBED_FILESYSTEM_H

#include "nesco/hal/include/DefaultFilesystem.h"

#include "mbed.h"
#include "BlockDevice.h"

#define NESCO_DEBUG
#ifdef NESCO_DEBUG
    #include "FATFileSystem.h"
    typedef FATFileSystem RealFileSystem;
#else
    #include "LittleFileSystem.h"
    typedef LittleFileSystem RealFileSystem;
#endif

namespace nesco::hal
{
    class MbedFilesystem : public DefaultFilesystem
    {
    public:
        void init();
    };
};

#endif
