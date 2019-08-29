#ifndef NESCO_OPCODE_H
#define NESCO_OPCODE_H

namespace nesco
{
    /**
     * Addressing mode
     */
    enum AddressingMode
    {
        Implied,            // implied in command
        Relative,           // PC relative
        Immediate = 0x00,   // #$00
        IndirectX = 0x00,   // ($00,X)
        ZeroPage  = 0x04,   // $00
        Absolute  = 0x0C,   // $0000
        IndirectY = 0x10,   // ($00),Y
        ZeropageX = 0x14,   // $00,X
        ZeropageY = 0x16,   // $00,Y
        AbsoluteY = 0x18,   // $0000,Y
        AbsoluteX = 0x1C,   // $0000,X
        Indirect  = 0x2C,   // ($0000)
    };

    /**
     * Opcode Set 0x00
     * 
     * opcode & 0x3 == 0x00
     */
    enum OpcodeSet_00
    {
        BIT = 0x20,     // N := b7; V := b6; Z := A and {adr}
        JMP = 0x40,     // PC := {adr}
        STY = 0x80,     // {adr} := Y
        LDY = 0xA0,     // Y := {adr}
        CPY = 0xC0,     // Y - {adr}
        CPX = 0xE0,     // X - {adr}
    };

    /**
     * Opcode Set 0x01
     * 
     * opcode & 0x3 == 0x01
     */
    enum OpcodeSet_01
    {
        ORA = 0x00,     // A := A or {adr}
        AND = 0x20,     // A := A and {adr}
        EOR = 0x40,     // A := A exor {adr}
        ADC = 0x60,     // A := A + {adr}
        STA = 0x80,     // {adr} := A
        LDA = 0xA0,     // A := {adr}
        CMP = 0xC0,     // A - {adr}
        SBC = 0xE0,     // A := A - {adr}
    };

    /**
     * Opcode Set 0x10
     * 
     * opcode & 0x3 == 0x10
     */
    enum OpcodeSet_10
    {
        ASL = 0x00,     // {adr} := {adr} * 2
        ROL = 0x20,     // {adr} := {adr} * 2 + C
        LSR = 0x40,     // {adr} := {adr} / 2
        ROR = 0x60,     // {adr} := {adr} / 2 + C * 128
        STX = 0x80,     // {adr} := X
        LDX = 0xA0,     // X := {adr}
        DEC = 0xC0,     // {adr} := {adr} - 1
        INC = 0xE0,     // {adr} := {adr} + 1
    };

    /**
     * Opcode Set implied addressing mode
     */
    enum OpcodeSet_Implied
    {
        BRK = 0x00,     // (SP)-- := PC; (SP)-- := P; PC := ($FFFE)
        PHP = 0x08,     // (SP)-- := P
        CLC = 0x18,     // C := 0
        JSR = 0x20,     // (SP)-- := PC; PC := {adr}
        PLP = 0x28,     // P := ++(SP)
        SEC = 0x38,     // C := 1
        RTI = 0x40,     // P := ++(SP) ; PC := ++(SP)
        PHA = 0x48,     // (SP)-- := A
        CLI = 0x58,     // I := 0
        RTS = 0x60,     // PC := ++(SP)
        PLA = 0x68,     // A := ++(SP)
        SEI = 0x78,     // I := 1
        DEY = 0x88,     // Y := Y - 1
        TXA = 0x8A,     // A := X
        TYA = 0x98,     // A := Y
        TXS = 0x9A,     // SP := X
        TAY = 0xA8,     // Y := A
        TAX = 0xAA,     // X := A
        CLV = 0xB8,     // V := 0
        TSX = 0xBA,     // X := SP
        INY = 0xC8,     // Y := Y + 1
        DEX = 0xCA,     // X := X - 1
        CLD = 0xD8,     // D := 0
        INX = 0xE8,     // X := X + 1
        NOP = 0xEA,     // NOP
        SED = 0xF8,     // D := 1
    };

    /**
     * Opcode Set branch command
     */
    enum OpcodeSet_Branch
    {
        BPL = 0x10,     // branch on N=0
        BMI = 0x30,     // branch on N=1
        BVC = 0x50,     // branch on V=0
        BVS = 0x70,     // branch on V=1
        BCC = 0x90,     // branch on C=0
        BCS = 0xB0,     // branch on C=1
        BNE = 0xD0,     // branch on Z=0
        BEQ = 0xF0,     // branch on Z=1
    };

    uint8_t Opcycles[0x100] = {
        /*      x0 x1 x2 x3 x4 x5 x6 x7 x8 x9 xA xB xC xD xE xF */    
        /* 0x */ 7, 6, 0, 8, 3, 3, 5, 5, 3, 2, 2, 2, 4, 4, 6, 6,
        /* 1x */ 2, 5, 0, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
        /* 2x */ 6, 6, 0, 8, 3, 3, 5, 5, 4, 2, 2, 2, 4, 4, 6, 6,
        /* 3x */ 2, 5, 0, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
        /* 4x */ 6, 6, 0, 8, 3, 3, 5, 5, 3, 2, 2, 2, 3, 4, 6, 6,
        /* 5x */ 2, 5, 0, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
        /* 6x */ 6, 6, 0, 8, 3, 3, 5, 5, 4, 2, 2, 2, 5, 4, 6, 6,
        /* 7x */ 2, 5, 0, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
        /* 8x */ 2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
        /* 9x */ 2, 6, 0, 6, 4, 4, 4, 4, 2, 5, 2, 5, 5, 5, 5, 5,
        /* Ax */ 2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
        /* Bx */ 2, 5, 0, 5, 4, 4, 4, 4, 2, 4, 2, 4, 4, 4, 4, 4,
        /* Cx */ 2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
        /* Dx */ 2, 5, 0, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
        /* Ex */ 2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
        /* Fx */ 2, 5, 0, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
    };

};

#endif
