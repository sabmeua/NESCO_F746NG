#ifndef NESCO_HAL_FILESYSTEM_H
#define NESCO_HAL_FILESYSTEM_H

#include <cstdint>
#include <vector>

namespace nesco::hal
{
    class FilesystemHal
    {
    public:
        virtual void load(const char *path) = 0;
    };
};

#endif
