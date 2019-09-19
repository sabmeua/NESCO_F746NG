#include "nesco/hal/include/DefaultFilesystem.h"

using namespace std;

namespace nesco::hal
{
    void DefaultFilesystem::init()
    {
    }

    NescoFileHandle DefaultFilesystem::open(const char *key, const char *mode)
    {
        int *i;
        return static_cast<NescoFileHandle>(i);
    }

    bool DefaultFilesystem::read(NescoFileHandle h, uint8_t *buff, uint32_t size)
    {
        return true;
    }

    bool DefaultFilesystem::write(NescoFileHandle h, uint8_t *buff, uint32_t size)
    {
        return true;
    }

    bool DefaultFilesystem::seek(NescoFileHandle h, uint32_t offset, uint8_t origin)
    {
        return true;
    }

    bool DefaultFilesystem::readLine(NescoFileHandle h, char *buff)
    {
        return true;
    }

    bool DefaultFilesystem::writeLine(NescoFileHandle h, const char *buff)
    {
        return true;
    }

    void DefaultFilesystem::close(NescoFileHandle h)
    {
    }
};
