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

