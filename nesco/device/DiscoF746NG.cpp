#include "nesco/device/DiscoF746NG.h"

namespace nesco::device
{
    BlockDevice *bd = BlockDevice::get_default_instance();
    NescoFileSystem fs("fs");

    DiscoF746NG::DiscoF746NG()
    {
        display = new DisplayDiscoF746NG();
        filesystem = new FilesystemDiscoF746NG();
        sound = new SoundDiscoF746NG();
        keypad = new KeypadDiscoF746NG();
    }

    void FilesystemDiscoF746NG::init()
    {
        if (fs.mount(bd)) {
            // Filesystem not found, need to format.
            // @ToDo: Abort
        }
    }

    NescoFileHandle FilesystemDiscoF746NG::open(const char *key, const char *mode)
    {
        FILE *fp = fopen(key, mode);
        if (!fp) {
            // @ToDo: throw Exception
        }

        return static_cast<NescoFileHandle>(fp);
    }

    bool FilesystemDiscoF746NG::read(NescoFileHandle h, uint8_t *buff, uint32_t size)
    {
        FILE *fp = static_cast<FILE *>(h);

        uint32_t result = fread(buff, sizeof(uint8_t), size, fp);
        return true;
    }

    bool FilesystemDiscoF746NG::write(NescoFileHandle h, uint8_t *buff, uint32_t size)
    {
        return true;
    }
};
