#ifndef NESCO_APU_H
#define NESCO_APU_H

#include <cstdint>

namespace nesco::core
{
    class Apu
    {
    public:
        void writeRegister(uint16_t addr, uint8_t data);
        uint8_t readRegister(uint16_t addr);

    private:
        // Registers
        union u_register {
            // For access by name
            struct {
                // Pulse Ch 1 : $4000 ~ $4003
                uint8_t PULSE1_CTRL1;   // W: Control register 1
                uint8_t PULSE1_CTRL2;   // W: Control register 2
                uint8_t PULSE1_FREQ1;   // W: Timer freq register 1
                uint8_t PULSE1_FREQ2;   // W: Timer freq register 2
                // Pulse Ch 2 : $4004 ~ $4007
                uint8_t PULSE2_CTRL1;   // W: Control register 1
                uint8_t PULSE2_CTRL2;   // W: Control register 2
                uint8_t PULSE2_FREQ1;   // W: Timer freq register 1
                uint8_t PULSE2_FREQ2;   // W: Timer freq register 2
                // Triangle Ch : $4008 ~ $400B
                uint8_t TRIANGLE_CTRL;  // W: Control register
                uint8_t TRIANGLE_RESV;  // -: Reserved
                uint8_t TRIANGLE_FREQ1; // W: Timer freq register 1
                uint8_t TRIANGLE_FREQ2; // W: Timer freq register 2
                // Noise Ch : $400C ~ $400F
                uint8_t NOISE_CTRL;     // W: Control register
                uint8_t NOISE_RESV;     // -: Reserved
                uint8_t NOISE_FREQ1;    // W: Timer freq register 1
                uint8_t NOISE_FREQ2;    // W: Timer freq register 2
                // DMC Ch : $4010 ~ $4013
                uint8_t DMC_CTRL1;      // W: Control register 1
                uint8_t DMC_CTRL2;      // W: Control register 2
                uint8_t DMC_ADDR;       // W: Sample address register
                uint8_t DMC_LENGTH;     // W: Sample length register

                uint8_t DUMMY_DMA;      // -: Padding 1byte : $4014
                uint8_t SOUND_CTRL;     // RW: Sound control register : $4015
                uint8_t DUMMY_PAD;      // -: Padding 1byte : $4016
                uint8_t SOUND_FRAME;    // W: Sound frame register : $4017
            } name;

            // For access by index (index <- addr % 0x4000)
            uint8_t index[0x18];
        } Register;

    };
};
#endif
