#include "CpuBus.h"

namespace nesco
{
    CpuBus::CpuBus(Ram *_ram)
    {
        ram = _ram;
    }

    CpuBus::~CpuBus()
    {
    }

    uint8_t CpuBus::read(uint16_t addr)
    {
        if (addr < 0x0800) {
            return ram->read(addr);
        } else {

        }
    }

    void CpuBus::write(uint16_t addr, uint8_t data)
    {
        if (addr < 0x0800) {
            ram->write(addr, data);
        } else {

        }
    }
};
