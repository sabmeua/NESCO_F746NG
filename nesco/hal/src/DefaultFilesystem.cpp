#include "nesco/hal/include/DefaultFilesystem.h"
#include "nesco_logger.h"

using namespace std;

namespace nesco::hal
{
    void DefaultFilesystem::init()
    {
    }

    NescoFileHandle DefaultFilesystem::open(const char *key, const char *mode)
    {
        FILE *fp = fopen(key, mode);
        if (!fp) {
            // @ToDo: throw Exception
        }

        return static_cast<NescoFileHandle>(fp);
    }

    bool DefaultFilesystem::read(NescoFileHandle h, uint8_t *buff, uint32_t size)
    {
        FILE *fp = static_cast<FILE *>(h);

        fread(buff, sizeof(uint8_t), size, fp);
        return true;
    }

    bool DefaultFilesystem::write(NescoFileHandle h, uint8_t *buff, uint32_t size)
    {
        FILE *fp = static_cast<FILE *>(h);
        uint32_t result = fwrite(buff, sizeof(uint8_t), size, fp);
        if (result < size) {
            return false;
        }
        return true;
    }

    bool DefaultFilesystem::seek(NescoFileHandle h, uint32_t offset, uint8_t origin)
    {
        FILE *fp = static_cast<FILE *>(h);
        if (fseek(fp, offset, origin)) {
            return false;
        }
        return true;
    }

    bool DefaultFilesystem::readLine(NescoFileHandle h, char *buff)
    {
        FILE *fp = static_cast<FILE *>(h);
        if (fgets(buff, 0x100, fp) == NULL) {
            return false;
        }
        return true;
    }

    bool DefaultFilesystem::writeLine(NescoFileHandle h, const char *buff)
    {
        FILE *fp = static_cast<FILE *>(h);
        fputs(buff, fp);
        uint32_t result = fwrite("\n", sizeof(char), 1, fp);
        if (result < 1) {
            return false;
        }
        return true;
    }

    void DefaultFilesystem::close(NescoFileHandle h)
    {
        FILE *fp = static_cast<FILE *>(h);
        fclose(fp);
    }
};
