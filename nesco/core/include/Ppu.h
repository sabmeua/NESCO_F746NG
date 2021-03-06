#ifndef NESCO_CORE_PPU_H
#define NESCO_CORE_PPU_H

#include <cstdint>
#include "PpuBus.h"
#include "Ram.h"

namespace nesco::core
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
     * ...
     * 220|       Z <- if this tile shows character "Z" in screen 0 and
     * 240|            the character ROM is mapped as below.
     * 260|            0x5A is written in address 0x0223.
     * 280|
     * 2A0|              char ROM $00 xx
     * 2C0|                       $01 xx
     * 2E0|                        ...
     * 300|                       $41 "A"
     * 320|                        ...
     * 340|                       $5A "Z"
     * 360|                        ...
     * 380|                       $01 xx
     * 3A0|
     *
     */

    typedef struct {
        uint16_t x;
        uint16_t y;
    } Pos;

    typedef struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    } Colors;

    const struct {
        int PreRender = 0;
        int RenderStart = 1;
        int RenderEnd = 240;
        int PostRender = 241;
        int VBlankStart = 242;
        int VBlankEnd = 261;
        int LineEnd = 262;
    } LineState;

    const struct {
        int FrameStart = 0;
        int FrameEnd = 255;
        int HBlankStart = 256;
        int HBlankEnd = 340;
        int CycleEnd = 341;
    } CycleState;

    enum PpuStatusFlag {
        VBlankFlag = 0x80,
        SpriteZeroHitFlag = 0x40,
        SpriteOverflowFlag = 0x20,
        VRAMAddrIncrementFlag = 0x04,
    };

    #define SPRITE_NUMS 0x100

    class Ppu
    {
    public:
        Ppu(PpuBus *_ppubus);
        ~Ppu();

        void reset();
        void step(uint16_t clk);

        uint8_t readRegister(uint16_t addr);
        void writeRegister(uint16_t addr, uint8_t data);

    private:
        PpuBus *bus;
        uint16_t scanline;
        uint16_t cycle;

        Ram oamData;    // sprite ram that read/write through OAMADDR/OAMDATA register

        uint16_t vramAddr;
        uint8_t vramAddrByteSel;

        // Registers
        union u_register{
            // For access by name
            struct {
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
                uint8_t PPUADDR;    // W:  VRAM address register
                uint8_t PPUDATA;    // RW: VRAM data register
            } name;

            // For access by index (index <- addr % 0x2000)
            uint8_t index[8];
        } Register;

        uint8_t OAMDMA;     // W:  OAM DMA register (High byte)

        static const Colors colors[64];

        void setFlag(PpuStatusFlag flag);
        void clearFlag(PpuStatusFlag flag);
        bool getFlag(PpuStatusFlag flag);
        bool isVBlank();

        void setSprite();
        void setBackground();

        uint16_t patternTableAddr() {
            return Register.name.PPUCTRL & 0x08 ? 0x1000 : 0x0000;
        }

        Pos tile() {
            return {uint16_t(scanline / 8), uint16_t(cycle / 8)};
        }
    };
};
#endif
