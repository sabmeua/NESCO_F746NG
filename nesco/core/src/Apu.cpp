#include "Apu.h"

namespace nesco::core
{
    class ApuChannel
    {
    public:
        ApuChannel(Apu *_apu) : apu(_apu) {};
        void envelope() {};
        void counter() {};
    private:
        Apu *apu;
    };

    class PulseChannel : public ApuChannel
    {
    public:
        PulseChannel(Apu *_apu) : ApuChannel(_apu) {};
    };

    class TriangleChannel : public ApuChannel
    {
    public:
        TriangleChannel(Apu *_apu) : ApuChannel(_apu) {};
    };

    class NoiseChannel : public ApuChannel
    {
    public:
        NoiseChannel(Apu *_apu) : ApuChannel(_apu) {};
    };

    class DmcChannel : public ApuChannel
    {
    public:
        DmcChannel(Apu *_apu) : ApuChannel(_apu) {};
    };

    Apu::Apu()
    {
        pulse1 = new PulseChannel(this);
        pulse2 = new PulseChannel(this);
        triangle = new TriangleChannel(this);
        noise = new NoiseChannel(this);
        dmc = new DmcChannel(this);
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
        uint16_t idx = addr % 0x4000;
        if (idx <= 0x17 && (idx != 0x14 || idx != 0x16)) {
            if (idx == 0x17) {
                data &= 0xC0;
            }
            Register.index[idx] = data;
        }
    }
    
    uint8_t Apu::readRegister(uint16_t addr)
    {
        uint8_t data = 0;
        if (addr == 0x4015) {
            data = Register.index[addr % 0x4000];
        }
        return data;
    }

    ApuFrameSequenceMode Apu::getFrameSequenceMode()
    {
        return static_cast<ApuFrameSequenceMode>(Register.name.SOUND_CTRL / 0x80);
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
