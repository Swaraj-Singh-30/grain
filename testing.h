#pragma once

#include <cassert>
#include <iostream>
#include "logic.h"

inline int byteToInt(const Byte& b) {
    int value = 0;

    for (int i = 0; i < 8; ++i) {
        if (b[i])
            value |= (1 << i);
    }

    return value;
}

inline void runGateTests() {

    // NAND
    assert(NAND(0,0) == 1);
    assert(NAND(0,1) == 1);
    assert(NAND(1,0) == 1);
    assert(NAND(1,1) == 0);

    // NOT
    assert(NOT(0) == 1);
    assert(NOT(1) == 0);

    // AND
    assert(AND(0,0) == 0);
    assert(AND(0,1) == 0);
    assert(AND(1,0) == 0);
    assert(AND(1,1) == 1);

    // OR
    assert(OR(0,0) == 0);
    assert(OR(0,1) == 1);
    assert(OR(1,0) == 1);
    assert(OR(1,1) == 1);

    // XOR
    assert(XOR(0,0) == 0);
    assert(XOR(0,1) == 1);
    assert(XOR(1,0) == 1);
    assert(XOR(1,1) == 0);

    // NOR
    assert(NOR(0,0) == 1);
    assert(NOR(0,1) == 0);
    assert(NOR(1,0) == 0);
    assert(NOR(1,1) == 0);

    // XNOR
    assert(XNOR(0,0) == 1);
    assert(XNOR(0,1) == 0);
    assert(XNOR(1,0) == 0);
    assert(XNOR(1,1) == 1);

    std::cout << "[PASS] Gate tests\n";
}

inline void runHalfAdderTests() {

    auto r = halfAdder(0,0);
    assert(r.sum == 0);
    assert(r.carry == 0);

    r = halfAdder(0,1);
    assert(r.sum == 1);
    assert(r.carry == 0);

    r = halfAdder(1,0);
    assert(r.sum == 1);
    assert(r.carry == 0);

    r = halfAdder(1,1);
    assert(r.sum == 0);
    assert(r.carry == 1);

    std::cout << "[PASS] Half Adder tests\n";
}

inline void runFullAdderTests() {

    auto r = fullAdder(0,0,0);
    assert(r.sum == 0);
    assert(r.carry == 0);

    r = fullAdder(0,0,1);
    assert(r.sum == 1);
    assert(r.carry == 0);

    r = fullAdder(0,1,0);
    assert(r.sum == 1);
    assert(r.carry == 0);

    r = fullAdder(0,1,1);
    assert(r.sum == 0);
    assert(r.carry == 1);

    r = fullAdder(1,0,0);
    assert(r.sum == 1);
    assert(r.carry == 0);

    r = fullAdder(1,0,1);
    assert(r.sum == 0);
    assert(r.carry == 1);

    r = fullAdder(1,1,0);
    assert(r.sum == 0);
    assert(r.carry == 1);

    r = fullAdder(1,1,1);
    assert(r.sum == 1);
    assert(r.carry == 1);

    std::cout << "[PASS] Full Adder tests\n";
}

inline void runAdd8Tests() {

    // 5 + 1 = 6
    {
        Byte A = {1,0,1,0,0,0,0,0};
        Byte B = {1,0,0,0,0,0,0,0};

        auto r = add8(A,B);

        assert(byteToInt(r.sum) == 6);
        assert(r.carry_out == 0);
    }

    // 10 + 20 = 30
    {
        Byte A = {0,1,0,1,0,0,0,0}; // 10
        Byte B = {0,0,1,0,1,0,0,0}; // 20

        auto r = add8(A,B);

        assert(byteToInt(r.sum) == 30);
        assert(r.carry_out == 0);
    }

    // 255 + 1 = overflow
    {
        Byte A = {1,1,1,1,1,1,1,1};
        Byte B = {1,0,0,0,0,0,0,0};

        auto r = add8(A,B);

        assert(byteToInt(r.sum) == 0);
        assert(r.carry_out == 1);
    }

    std::cout << "[PASS] Add8 tests\n";
}

inline void runDLatchTests() {

    DLatch latch;

    assert(latch.output() == 0);

    latch.tick(true, true);
    assert(latch.output() == 1);

    // should hold value
    latch.tick(false, false);
    assert(latch.output() == 1);

    latch.tick(true, false);
    assert(latch.output() == 0);

    std::cout << "[PASS] DLatch tests\n";
}

inline void runDFlipFlopTests() {

    DFlipFlop ff;

    assert(ff.output() == 0);

    ff.tick(true);
    assert(ff.output() == 1);

    ff.tick(false);
    assert(ff.output() == 0);

    ff.tick(true);
    assert(ff.output() == 1);

    std::cout << "[PASS] DFlipFlop tests\n";
}

inline void runAllTests() {

    runGateTests();
    runHalfAdderTests();
    runFullAdderTests();
    runAdd8Tests();
    runDLatchTests();
    runDFlipFlopTests();

    std::cout << "\n=== ALL TESTS PASSED ===\n";
}