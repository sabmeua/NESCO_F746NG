#include "nesco/hal/include/MbedFilesystem.h"

namespace nesco::hal
{
    BlockDevice *bd = BlockDevice::get_default_instance();
    RealFileSystem fs("fs");

    void MbedFilesystem::init()
    {
        if (fs.mount(bd)) {
            // Filesystem not found, need to format.
            // @ToDo: Abort
        }
    }
};
