#pragma once

#include <array>
#include <cstdint>
using Byte = std::array<bool, 8>; // index 0 = LSB

// BYTE UTILITIES
inline Byte intToByte(uint8_t value)
{
    Byte b{};

    for (int i = 0; i < 8; ++i)
        b[i] = (value >> i) & 1;

    return b;
}

inline uint8_t byteToInt(const Byte& b)
{
    uint8_t value = 0;

    for (int i = 0; i < 8; ++i)
    {
        if (b[i])
            value |= (1 << i);
    }

    return value;
}

// =====================================================
// GATES
// =====================================================

inline bool NAND(bool a, bool b)
{
    return !(a && b);
}

inline bool NOT(bool a)
{
    return NAND(a, a);
}

inline bool AND(bool a, bool b)
{
    return NOT(NAND(a, b));
}

inline bool OR(bool a, bool b)
{
    return NAND(NOT(a), NOT(b));
}

inline bool XOR(bool a, bool b)
{
    return NAND(
        NAND(a, NAND(a, b)),
        NAND(b, NAND(a, b))
    );
}

inline bool NOR(bool a, bool b)
{
    return NOT(OR(a, b));
}

inline bool XNOR(bool a, bool b)
{
    return NOT(XOR(a, b));
}

// =====================================================
// ADDERS
// =====================================================

struct HalfAdderResult
{
    bool sum;
    bool carry;
};

inline HalfAdderResult halfAdder(bool a, bool b)
{
    return {
        XOR(a, b),
        AND(a, b)
    };
}

struct FullAdderResult
{
    bool sum;
    bool carry;
};

inline FullAdderResult fullAdder(
    bool a,
    bool b,
    bool carryIn
)
{
    return {
        XOR(carryIn, XOR(a, b)),
        OR(
            OR(
                AND(a, b),
                AND(b, carryIn)
            ),
            AND(a, carryIn)
        )
    };
}

struct Add8Result
{
    Byte sum{};
    bool carryOut{};
};

inline Add8Result add8(
    const Byte& A,
    const Byte& B
)
{
    Add8Result result;

    bool carry = false;

    for (int i = 0; i < 8; ++i)
    {
        auto r = fullAdder(
            A[i],
            B[i],
            carry
        );

        result.sum[i] = r.sum;
        carry = r.carry;
    }

    result.carryOut = carry;

    return result;
}

// =====================================================
// LATCHES / FLIP FLOPS
// =====================================================

class DLatch
{
    bool q = false;

public:

    void tick(bool enable, bool d)
    {
        if (enable)
            q = d;
    }

    bool output() const
    {
        return q;
    }
};

class DFlipFlop
{
    bool q = false;
    bool d = false;

public:
    void setInput(bool value)
    {
        d = value;
    }

    void commit()
    {
        q = d;
    }

    bool output() const
    {
        return q;
    }
};

// =====================================================
// MUX
// =====================================================

inline bool MUX2(
    bool a,
    bool b,
    bool sel
)
{
    return OR(
        AND(NOT(sel), a),
        AND(sel, b)
    );
}

inline bool MUX4(
    bool a,
    bool b,
    bool c,
    bool d,
    bool s1,
    bool s0
)
{
    bool upper = MUX2(a, b, s0);
    bool lower = MUX2(c, d, s0);

    return MUX2(
        upper,
        lower,
        s1
    );
}

inline bool MUX8(
    bool a, bool b, bool c, bool d,
    bool e, bool f, bool g, bool h,
    bool s2, bool s1, bool s0
)
{
    return MUX2(
        MUX4(a,b,c,d,s1,s0),
        MUX4(e,f,g,h,s1,s0),
        s2
    );
}

// =====================================================
// REGISTER
// =====================================================

class Register8
{
    DFlipFlop bits[8];
    Byte next{};

public:

    void setInput(
        bool load,
        const Byte& input
    )
    {
        for (int i = 0; i < 8; ++i)
        {
            next[i] = MUX2(
                bits[i].output(),
                input[i],
                load
            );
        }
    }

    void commit()
    {
        for (int i = 0; i < 8; ++i)
            bits[i].setInput(next[i]);

        for (int i = 0; i < 8; ++i)
            bits[i].commit();
    }

    Byte output() const
    {
        Byte out{};

        for (int i = 0; i < 8; ++i)
            out[i] = bits[i].output();

        return out;
    }

    void load(const Byte& value)
    {
        setInput(true, value);
        commit();
    }
};

// =====================================================
// PROGRAM COUNTER
// =====================================================

class ProgramCounter
{
    Register8 reg;

public:

    enum class Mode
    {
        Hold,
        Increment,
        Load
    };

    void tick(
        Mode mode,
        const Byte& loadValue = {}
    )
    {
        Byte current = reg.output();

        Byte next = current;

        switch (mode)
        {
            case Mode::Hold:
                break;

            case Mode::Increment:
            {
                next = add8(
                    current,
                    intToByte(1)
                ).sum;
                break;
            }

            case Mode::Load:
            {
                next = loadValue;
                break;
            }
        }

        reg.load(next);
    }

    Byte output() const
    {
        return reg.output();
    }
};