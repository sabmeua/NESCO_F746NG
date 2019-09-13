#include "Apu.h"

namespace nesco::core
{
    Apu::Apu()
    {
        pulse1 = new PulseChannel();
        pulse2 = new PulseChannel();
        triangle = new TriangleChannel();
        noise = new NoiseChannel();
        dmc = new DmcChannel();
        cycle = 0;
    }

    void Apu::step()
    {
        ApuFrameSequenceMode mode = getFrameSequenceMode();
        switch(mode) {
            case SequenceMode4Step:
                if (1) {
                    envelope();
                }
                if (cycle % 2 == 1) {
                    counter();
                }
                if (cycle == 3) {
                    irqflag(true);
                }
                break;
            case SequenceMode5Step:
                if (cycle <= 3) {
                    envelope();
                    if (cycle % 2 == 0) {
                        counter();
                    }
                }
                break;
            default:
                break;
        }
        if (++cycle == (4 + mode)) {
            cycle = 0;
        }
    }

    void Apu::writeRegister(uint16_t addr, uint8_t data)
    {
        if (addr <= 0x4003) {
            pulse1->writeRegister(addr, data);
        } else if (addr <= 0x4007) {
            pulse2->writeRegister(addr, data);
        } else if (addr <= 0x400B) {
            triangle->writeRegister(addr, data);
        } else if (addr <= 0x400F) {
            noise->writeRegister(addr, data);
        } else if (addr <= 0x4013) {
            dmc->writeRegister(addr, data);
        } else if (addr == 0x4015) {
            SOUND_CTRL = data;
        } else if (addr == 0x4017) {
            SOUND_FRAME = data & 0xC0;
        }
    }
    
    uint8_t Apu::readRegister(uint16_t addr)
    {
        uint8_t data = 0;
        if (addr == 0x4015) {
            data = SOUND_CTRL;
        }
        return data;
    }

    ApuFrameSequenceMode Apu::getFrameSequenceMode()
    {
        return static_cast<ApuFrameSequenceMode>(SOUND_CTRL / 0x80);
    }

    void Apu::envelope()
    {
        pulse1->envelope();
        pulse2->envelope();
        noise->envelope();
    }

    void Apu::counter()
    {
        pulse1->counter();
        pulse2->counter();
        triangle->counter();
        noise->counter();
    }

    void Apu::irqflag(bool set)
    {
    }

};
