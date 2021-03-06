#include "Ppu.h"
#include "Emu.h"
#include "nesco_logger.h"

namespace nesco::core
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

    Ppu::Ppu(PpuBus *_ppubus) : bus(_ppubus), oamData(0x100), vramAddrByteSel(1)
    {
    }

    Ppu::~Ppu()
    {
    }

    void Ppu::reset()
    {
        vramAddrByteSel = 1;
        cycle = scanline = vramAddr = 0;
    }

    void Ppu::step(uint16_t clk)
    {
        if (scanline <= LineState.PreRender) {
            setSprite();
        } else if (scanline <= LineState.RenderEnd) {
            if (cycle <= CycleState.FrameEnd) {
                if (scanline % 8 == 0) {
                    setBackground();
                }
            } else if (cycle <= CycleState.HBlankEnd) {

            }
        } else if (scanline <= LineState.PostRender) {
        } else if (scanline == LineState.VBlankStart) {
        } else if (scanline <= LineState.VBlankEnd) {
        } else {
            Emu::abort("Invalid render state");
        }

        if (++cycle >= CycleState.CycleEnd) {
            if (++scanline >= LineState.LineEnd) {
                scanline = 0;
            }
            cycle = 0;
        }
    }

    uint8_t Ppu::readRegister(uint16_t addr)
    {
        switch (addr) {
            case 0x2004:
                Register.name.OAMDATA = oamData.read(Register.name.OAMADDR);
                break;
            case 0x2007:
                // @ToDo: read VRAM
                if (getFlag(VRAMAddrIncrementFlag)) {
                    vramAddr += 32;
                } else {
                    vramAddr += 1;
                }
                break;
            default:
                break;
        }
        return Register.index[addr % 0x2000];
    }

    void Ppu::writeRegister(uint16_t addr, uint8_t data)
    {
        if (addr == 0x2006) {
            if (vramAddrByteSel == 0) {
                vramAddr = (Register.name.PPUADDR << 8)  | data;
                vramAddrByteSel = 1;
            } else {
                vramAddrByteSel = 0;
            }
        }
        Register.index[addr % 0x2000] = data;
        switch (addr) {
            case 0x2004:
                oamData.write(Register.name.OAMADDR, Register.name.OAMDATA);
                Register.name.OAMADDR++;
                break;
            case 0x2007:
                // @ToDo: write VRAM
                if (getFlag(VRAMAddrIncrementFlag)) {
                    vramAddr += 32;
                } else {
                    vramAddr += 1;
                }
            default:
                break;
        }
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

    void Ppu::setSprite()
    {
         uint16_t ptnAddrBase = patternTableAddr();
         for (int i = 0; i < SPRITE_NUMS; i += 4) {
         }
    }

    void Ppu::setBackground()
    {
    }
}
