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
     * VRAM ----------------------------------------------------
     * $2000 - $23BF    Screen 0 Name table
     * $23C0 - $23FF    Screen 0 Attribute table
     * $2400 - $27BF    Screen 1 Name table
     * $27C0 - $27FF    Screen 1 Attribute table
     * $2800 - $2BBF    Screen 2 Name table (mirrored $2000-$23BF)
     * $2BC0 - $2BFF    Screen 2 Attribute table (mirroed $23C0-$23FF)
     * $2C00 - $2FBF    Screen 3 Name table (mirrored $2400-$27BF)
     * $2FC0 - $2FFF    Screen 3 Attribute table (mirroed $27C0-$2FFF)
     * ---------------------------------------------------------
     * $3000 - $3EFF    Unused (mirrored $2000-$2EFF)
     * $3F00 - $3F0F    BG palette
     * $3F10 - $3F1F    Sprite palette
     * $3F20 - $3FFF    Unused (mirrored $3F00-$3F1F)
     * $4000 - $FFFF    Unused (mirrored $0000-$3FFF)
     *
     */

    /**
     * Virtual screen on VRAM
     *
     *   1 screen = 256 * 240 pixel
     *   1 tile = 8 x 8 pixels -> 32 x 30 = 960 tiles
     *   1 block = 2 x 2 blocks -> 16 x 15 = 240 blocks
     *
     *    | 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
     *    | 0 1 2 3 4 5 6 7 8 9 A B C D E F 0 1 2 3 4 5 6 7 8 9 A B C D E F
     * ---+----------------------------------------------------------------
     *  00|[]   <- 1tile: Each tiles are applied a sprite No.
     *  20|
     *  40|[  ] <- 1block(2x2 tiles): Each blocks are applied a BG No.
     *  60|[  ]
     *  80|
     *  A0|
     *  C0|
     *  E0|
     * 100|
     * 120|
     * 140|
     * 160|
     * 180|
     * 1A0|
     * 1C0|       Z <- if this tile shows character "Z" in screen 0 and
     * 1E0|            the character ROM is mapped as below.
     * 200|            0x5A is written in address 0x01C3.
     * 220|
     * 240|              char ROM $00 xx
     * 260|                       $01 xx
     * 280|                        ...
     * 2A0|                       $41 "A"
     * 2C0|                        ...
     * 2E0|                       $5A "Z"
     * 300|                        ...
     * 320|                       $01 xx
     * 340|
     * 360|
     * 380|
     * 3A0|
     *
     */

    typedef struct st_colors {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    } Colors;

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

        static const Colors colors[64];
    };
};
#endif
