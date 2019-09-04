#ifndef NESCO_PPU_H
#define NESCO_PPU_H

#include <cstdint>
#include "PpuBus.h"

namespace nesco
{
    /**
     * Memory map
     *
     * $0000 - $0FFF    Pattern table Low
     * $1000 - $1FFF    Pattern table High
     * $2000 - $23BF    Name table 0
     * $23C0 - $23FF    Attribute table 0
     * $2400 - $27BF    Name table 1
     * $27C0 - $27FF    Attribute table 1
     * $2800 - $2BBF    Name table 2 (mirrored $2000-$23BF)
     * $2BC0 - $2BFF    Attribute table 2 (mirroed $23C0-$23FF)
     * $2C00 - $2FBF    Name table 3 (mirrored $2400-$27BF)
     * $2FC0 - $2FFF    Attribute table 3 (mirroed $27C0-$2FFF)
     * $3000 - $3EFF    Unused (mirrored $2000-$2EFF)
     * $3F00 - $3F0F    BG palette
     * $3F10 - $3F1F    Sprite Palette
     * $3F20 - $3FFF    Unused (mirrored $3F00-$3F1F)
     * $4000 - $FFFF    Unused (mirrored $0000-$3FFF)
     *
     */

    class Ppu
    {
    public:
        Ppu(PpuBus *_ppubus);
        ~Ppu();

        void reset();

    private:
        PpuBus *bus;
        
        // Registers
        uint8_t PPUCTRL;    // W:  Control register 1
                            // LSB
                            // 0-1:NN Base nametable address
                            //      (0: $2000; 1: $2400; 2: $2800; 3: $2C00)
                            // 2  :I VRAM address increment per CPU read/write of PPUDATA
                            //      (0: add 1, going across; 1: add 32, going down)
                            // 3  :S Sprite pattern table address for 8x8 sprites
                            //      (0: $0000; 1: $1000; ignored in 8x16 mode)
                            // 4  :B Background pattern table address (0: $0000; 1: $1000)
                            // 5  :H Sprite size (0: 8x8 pixels; 1: 8x16 pixels)
                            // 6  :P PPU master/slave select
                            //      (0: read backdrop from EXT pins; 1: output color on EXT pins)
                            // 7  :V Generate an NMI at the start of the VBlank interval
                            //      (0: off; 1: on)
                            // MSB

        uint8_t PPUMASK;    // W:  Control register 2
                            // LSB
                            // 0  :G Greyscale (0: normal color, 1: produce a greyscale display)
                            // 1  :m (1: Show background in leftmost 8 pixels of screen, 0: Hide)
                            // 2  :M (1: Show sprites in leftmost 8 pixels of screen, 0: Hide)
                            // 3  :b (1: Show background)
                            // 4  :s (1: Show sprites)
                            // 5-7:B BG color (0: black; 1: blue; 2: green; 4: red)
                            // MSB

        uint8_t PPUSTATUS;  // R:  Status register
                            // LSB
                            // 0-4:. Unused
                            // 5  :O Sprite overflow
                            // 6  :S Sprite 0 Hit
                            // 7  :V VBlank has started (0: not in vblank; 1: in vblank)
                            // MSB
        
        uint8_t OAMADDR;    // W:  OAM sprite address register
        uint8_t OAMDATA;    // RW: OAM sprite data register
        uint8_t PPUSCROLL;  // W:  BG scroll offset register
        uint8_t PPUADDR;    // W:  PPU memory address register
        uint8_t PPUDATA;    // RW: PPU Memory data register
        uint8_t OAMDMA;     // W:  OAM DMA register (High byte)
    };
};
#endif
