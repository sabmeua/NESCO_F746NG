#ifndef NESCO_MAPPER_H
#define NESCO_MAPPER_H

namespace nesco::core
{
    class Mapper
    {
    public:
        virtual uint8_t read(uint16_t addr) = 0;
        virtual void write(uint16_t addr, uint8_t data) = 0;
    };

    class Mapper0 : public Mapper
    {
    public:
        virtual uint8_t read(uint16_t addr) { return 0; }
        virtual void write(uint16_t addr, uint8_t data) {}
    };
};

#endif
