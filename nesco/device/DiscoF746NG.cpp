#include "nesco/device/DiscoF746NG.h"

namespace nesco::device
{
    BlockDevice *bd = BlockDevice::get_default_instance();
    NescoFileSystem fs("fs");

    void DiscoF746NG::reset()
    {
        if (fs.mount(bd)) {
            // Filesystem not found, need to format.
            // @ToDo: Abort
        }
    }

    NescoFileHandle DiscoF746NG::open(const char *key, const char *mode)
    {
        FILE *fp = fopen(key, mode);
        if (!fp) {
            // @ToDo: throw Exception
        }

        return static_cast<NescoFileHandle>(fp);
    }
};
