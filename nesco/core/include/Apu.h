#ifndef NESCO_APU_H
#define NESCO_APU_H

#include <cstdint>

namespace nesco::core
{
    enum ApuFrameSequenceMode {
        /**
         * 4 step mode
         *
         * step     0 1 2 3
         * ----------------
         * irqflag  - - - o
         * counter  - o - o
         * envelope o o o o
         */
        SequenceMode4Step,
        /**
         * 5 step mode
         *
         * step     0 1 2 3 4
         * ------------------
         * irqflag  - - - - -
         * counter  o - o - -
         * envelope o o o o -
         */
        SequenceMode5Step,
    };

    class ApuChannel
    {
    public:
        void envelope() {};
        void counter() {};
        uint8_t readRegister(uint16_t addr) {
            return Register.index[addr % 0x4000 % 4];
        };
        void writeRegister(uint16_t addr, uint8_t data) {
            Register.index[addr % 0x4000 % 4] = data;
        };
    protected:
        // Registers
        union u_register {
            // For access by name
            struct {
                uint8_t CTRL1;  // W: Control register 1
                uint8_t CTRL2;  // W: Control register 2
                uint8_t FREQ1;  // W: Timer freq register 1
                uint8_t FREQ2;  // W: Timer freq register 2
            } name;
            // For access by index (index <- addr % 0x4000 % 4)
            uint8_t index[4];
        } Register;
    };

    class PulseChannel : public ApuChannel
    {
    };

    class TriangleChannel : public ApuChannel
    {
    };

    class NoiseChannel : public ApuChannel
    {
    };

    class DmcChannel : public ApuChannel
    {
    };

    class Apu
    {
    public:
        Apu();
        void step();
        void writeRegister(uint16_t addr, uint8_t data);
        uint8_t readRegister(uint16_t addr);

    private:
        PulseChannel *pulse1;
        PulseChannel *pulse2;
        TriangleChannel *triangle;
        NoiseChannel *noise;
        DmcChannel *dmc;

        uint8_t cycle;

        // Registers
        uint8_t SOUND_CTRL;     // RW: Sound control register : $4015
        uint8_t SOUND_FRAME;    // W: Sound frame register : $4017

        void counter();
        void envelope();
        void irqflag(bool set);

        ApuFrameSequenceMode getFrameSequenceMode();
    };
};
#endif
