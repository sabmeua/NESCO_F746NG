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

    FILE *DiscoF746NG::load(const char *path)
    {
        cartridgeFile = fopen(path, "r");
        if (!cartridgeFile) {
            // @ToDo: abort
        }

        return cartridgeFile;
    }
};
