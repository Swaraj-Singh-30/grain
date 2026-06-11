#pragma once
#include <array>

using Byte = std::array<bool, 8>;

// LOGIC GATES 
inline bool NAND(bool a, bool b){
    return !(a && b);
}

inline bool NOT(bool a){
    return NAND(a, a);
}

inline bool AND(bool a, bool b){
    return NOT(NAND(a, b));
}

inline bool OR(bool a, bool b){
    return NAND(NOT(a), NOT(b));
}

inline bool XOR(bool a, bool b){
    return NAND(NAND(a, NAND(a, b)),
                NAND(b, NAND(a, b)));
}

inline bool NOR(bool a, bool b){
    return NOT(OR(a,b));
}

inline bool XNOR(bool a, bool b){
    return NOT(XOR(a,b));
}


// ADDERS
struct HalfAdderResult {
    bool sum;
    bool carry;
};

inline HalfAdderResult halfAdder(bool a, bool b){
    return {XOR(a, b), AND(a, b)};
}

struct FullAdderResult {
    bool sum;
    bool carry;
};

inline FullAdderResult fullAdder(bool a, bool b, bool c){
    return {
        XOR(c, XOR(a, b)),
        OR(OR(AND(a, b), AND(b, c)), AND(a, c))
    };
}


// 8-bit adder
struct Add8Result {
    Byte sum;
    bool carry_out;
};

inline Add8Result add8(const Byte& A, const Byte& B) {
    Add8Result result;

    bool carry = false;

    for (int i = 0; i < 8; i++) {
        FullAdderResult r = fullAdder(A[i], B[i], carry);
        result.sum[i] = r.sum;
        carry = r.carry;
    }
    result.carry_out = carry;
    return result;
}

// D-Latch and flip flops
class DLatch {
    bool q = false;

public:
    void tick(bool enable, bool d) {
        if(enable)
            q = d;
    }
    bool output() const { return q; }
};


class DFlipFlop {
    bool q = false;
public:
    void tick(bool d){
        q = d;
    }
    bool output() const { return q; }
};

// MUX & DEMUX
inline bool MUX2(bool a, bool b, bool sel){
    return OR(
        AND(NOT(sel), a),
        AND(sel, b)
    );
}

// Y = S₁'S₀'I₀ + S₁'S₀I₁ + S₁S₀'I₂ + S₁S₀I₃
inline bool MUX4(
    bool a,
    bool b,
    bool c,
    bool d,
    bool s1,
    bool s0
){
    bool upper = MUX2(a, b, s0);
    bool lower = MUX2(c, d, s0);

    return MUX2(upper, lower, s1);
}


inline bool MUX8(
    bool a,bool b,bool c,bool d,
    bool e,bool f,bool g,bool h,
    bool s2,bool s1,bool s0
){
    return MUX2(
        MUX4(a,b,c,d,s1,s0),
        MUX4(e,f,g,h,s1,s0),
        s2
    );
}

// Register

