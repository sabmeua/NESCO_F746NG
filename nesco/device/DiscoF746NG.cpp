#include "nesco/device/DiscoF746NG.h"

namespace nesco::device
{
    BlockDevice *bd = BlockDevice::get_default_instance();
    FATFileSystem fs("sd");

    void DiscoF746NG::reset()
    {
        if (fs.mount(bd)) {
            // Filesystem not found, need to format.
            // @ToDo: Abort
        }
    }

    ifstream &DiscoF746NG::load(const char *path)
    {
        cartridgeFile.open(path, ios::in);
        if (!cartridgeFile) {
            // @ToDo: abort
        }

        return cartridgeFile;
    }
};
