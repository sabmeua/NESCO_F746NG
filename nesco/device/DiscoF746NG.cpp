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

        if (cartridgefp) {
            fclose(cartridgefp);
        }
    }

    FILE *DiscoF746NG::load(const char *path)
    {
        if (cartridgefp) {
            fclose(cartridgefp);
        }

        cartridgefp = fopen(path, "r");
        if (!cartridgefp) {
            // @ToDo: throw Exception
        }

        return cartridgefp;
    }
};
