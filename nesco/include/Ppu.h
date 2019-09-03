#ifndef NESCO_PPU_H
#define NESCO_PPU_H

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
    };
};
#endif
