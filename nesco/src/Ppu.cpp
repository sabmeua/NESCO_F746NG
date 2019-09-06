#include "Ppu.h"

namespace nesco
{
    const Colors Ppu::colors[] = {
        {0x80, 0x80, 0x80}, {0x00, 0x3D, 0xA6}, {0x00, 0x12, 0xB0}, {0x44, 0x00, 0x96},
        {0xA1, 0x00, 0x5E}, {0xC7, 0x00, 0x28}, {0xBA, 0x06, 0x00}, {0x8C, 0x17, 0x00},
        {0x5C, 0x2F, 0x00}, {0x10, 0x45, 0x00}, {0x05, 0x4A, 0x00}, {0x00, 0x47, 0x2E},
        {0x00, 0x41, 0x66}, {0x00, 0x00, 0x00}, {0x05, 0x05, 0x05}, {0x05, 0x05, 0x05},
        {0xC7, 0xC7, 0xC7}, {0x00, 0x77, 0xFF}, {0x21, 0x55, 0xFF}, {0x82, 0x37, 0xFA},
        {0xEB, 0x2F, 0xB5}, {0xFF, 0x29, 0x50}, {0xFF, 0x22, 0x00}, {0xD6, 0x32, 0x00},
        {0xC4, 0x62, 0x00}, {0x35, 0x80, 0x00}, {0x05, 0x8F, 0x00}, {0x00, 0x8A, 0x55},
        {0x00, 0x99, 0xCC}, {0x21, 0x21, 0x21}, {0x09, 0x09, 0x09}, {0x09, 0x09, 0x09},
        {0xFF, 0xFF, 0xFF}, {0x0F, 0xD7, 0xFF}, {0x69, 0xA2, 0xFF}, {0xD4, 0x80, 0xFF},
        {0xFF, 0x45, 0xF3}, {0xFF, 0x61, 0x8B}, {0xFF, 0x88, 0x33}, {0xFF, 0x9C, 0x12},
        {0xFA, 0xBC, 0x20}, {0x9F, 0xE3, 0x0E}, {0x2B, 0xF0, 0x35}, {0x0C, 0xF0, 0xA4},
        {0x05, 0xFB, 0xFF}, {0x5E, 0x5E, 0x5E}, {0x0D, 0x0D, 0x0D}, {0x0D, 0x0D, 0x0D},
        {0xFF, 0xFF, 0xFF}, {0xA6, 0xFC, 0xFF}, {0xB3, 0xEC, 0xFF}, {0xDA, 0xAB, 0xEB},
        {0xFF, 0xA8, 0xF9}, {0xFF, 0xAB, 0xB3}, {0xFF, 0xD2, 0xB0}, {0xFF, 0xEF, 0xA6},
        {0xFF, 0xF7, 0x9C}, {0xD7, 0xE8, 0x95}, {0xA6, 0xED, 0xAF}, {0xA2, 0xF2, 0xDA},
        {0x99, 0xFF, 0xFC}, {0xDD, 0xDD, 0xDD}, {0x11, 0x11, 0x11}, {0x11, 0x11, 0x11},
    };

    Ppu::Ppu(PpuBus *_ppubus) : bus(_ppubus)
    {
    }

    Ppu::~Ppu()
    {
    }

    void Ppu::reset()
    {
        cycle = scanline = 0;
    }

    void Ppu::step()
    {
        if (scanline <= LineState.PreRender) {

        } else if (scanline <= LineState.Render) {
            if (cycle <= CycleState.Frame) {

            } else if (cycle <= CycleState.HBlank) {

            }
        } else if (scanline <= LineState.PostRender) {

        } else if (scanline <= LineState.VBlank) {

        } else {
            // @ToDo: implement Abort
        }

        if (cycle++ >= CycleState.CycleEnd) {
            if (scanline++ > LineState.LineEnd) {
                scanline = 0;
            }
            cycle = 0;
        }
    }

    uint8_t Ppu::readRegister(uint16_t addr)
    {
        return Register.index[addr % 0x2000];
    }

    void Ppu::writeRegister(uint16_t addr, uint8_t data)
    {
        Register.index[addr % 0x2000] = data;
    }

    void Ppu::setFlag(PpuStatusFlag flag)
    {
        Register.name.PPUSTATUS |= flag;
    }

    void Ppu::clearFlag(PpuStatusFlag flag)
    {
        Register.name.PPUSTATUS &= ~flag;
    }

    bool Ppu::getFlag(PpuStatusFlag flag)
    {
        return Register.name.PPUSTATUS & flag;
    }

    bool Ppu::isVBlank()
    {
        return getFlag(VBlankFlag);
    }
}
