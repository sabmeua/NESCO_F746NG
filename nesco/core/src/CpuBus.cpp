#include "CpuBus.h"

namespace nesco::core
{
    CpuBus::CpuBus(Ram *_ram, Ppu *_ppu, Apu *_apu, Dma *_dma) :
        ram(_ram), ppu(_ppu), apu(_apu), dma(_dma)
    {
    }

    CpuBus::~CpuBus()
    {
    }

    uint8_t CpuBus::read(uint16_t addr)
    {
        if (addr < 0x0800) {            // RAM access
            return ram->read(addr);
        } else if (addr < 0x2000) {     // RAM mirror * 3
            return ram->read(addr % 0x0800);
        } else if (addr < 0x2008) {     // PPU Registers access
            return ppu->readRegister(addr);
        } else if (addr < 0x4000) {     // PPU Registers mirror * 1023
            return ppu->readRegister((addr % 8) | 0x2000);
        } else if (addr == 0x4016 || addr == 0x4017) {  // Pad

        } else {
            return 0;
        }
    }

    uint16_t CpuBus::write(uint16_t addr, uint8_t data)
    {
        uint16_t exCycle = 0;

        if (addr < 0x0800) {            // RAM access
            ram->write(addr, data);
        } else if (addr < 0x2000) {     // RAM mirror * 3
            ram->write(addr % 0x0800, data);
        } else if (addr < 0x2008) {     // PPU Registers access
            ppu->writeRegister(addr, data);
        } else if (addr < 0x4000) {     // PPU Registers mirror * 1023
            ppu->writeRegister((addr % 8) | 0x2000, data);
        } else if (addr == 0x4014) {    // DMA
            exCycle = 514;
        } else if (addr == 0x4016) {  // Pad

        } else if (addr < 0x4020) {     // APU
            apu->writeRegister(addr, data);
        } else {

        }

        return exCycle;
    }
};
