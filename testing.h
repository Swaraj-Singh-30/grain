#pragma once

#include <cassert>
#include <iostream>
#include "logic.h"


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

    {
        Byte A = intToByte(5);
        Byte B = intToByte(1);

        auto r = add8(A, B);

        assert(byteToInt(r.sum) == 6);
        assert(r.carryOut == 0);
    }

    {
        Byte A = intToByte(10);
        Byte B = intToByte(20);

        auto r = add8(A, B);

        assert(byteToInt(r.sum) == 30);
        assert(r.carryOut == 0);
    }

    {
        Byte A = intToByte(255);
        Byte B = intToByte(1);

        auto r = add8(A, B);

        assert(byteToInt(r.sum) == 0);
        assert(r.carryOut == 1);
    }

    // Exhaustive-ish verification
    for (int a = 0; a < 256; ++a) {
        for (int b = 0; b < 256; ++b) {

            auto r = add8(intToByte(a), intToByte(b));

            int expected = a + b;

            assert(byteToInt(r.sum) == (expected & 0xFF));
            assert(r.carryOut == (expected > 255));
        }
    }

    std::cout << "[PASS] Add8 tests\n";
}

inline void runMUXTests() {

    // MUX2
    assert(MUX2(0,1,0) == 0);
    assert(MUX2(0,1,1) == 1);

    assert(MUX2(1,0,0) == 1);
    assert(MUX2(1,0,1) == 0);

    // MUX4
    assert(MUX4(1,0,0,0,0,0) == 1); // a
    assert(MUX4(0,1,0,0,0,1) == 1); // b
    assert(MUX4(0,0,1,0,1,0) == 1); // c
    assert(MUX4(0,0,0,1,1,1) == 1); // d

    // MUX8
    assert(MUX8(1,0,0,0,0,0,0,0,0,0,0) == 1); // a
    assert(MUX8(0,1,0,0,0,0,0,0,0,0,1) == 1); // b
    assert(MUX8(0,0,1,0,0,0,0,0,0,1,0) == 1); // c
    assert(MUX8(0,0,0,1,0,0,0,0,0,1,1) == 1); // d
    assert(MUX8(0,0,0,0,1,0,0,0,1,0,0) == 1); // e
    assert(MUX8(0,0,0,0,0,1,0,0,1,0,1) == 1); // f
    assert(MUX8(0,0,0,0,0,0,1,0,1,1,0) == 1); // g
    assert(MUX8(0,0,0,0,0,0,0,1,1,1,1) == 1); // h

    std::cout << "[PASS] MUX tests\n";
}

inline void runDLatchTests() {

    DLatch latch;

    assert(latch.output() == 0);

    latch.tick(true, true);
    assert(latch.output() == 1);

    latch.tick(false, false);
    assert(latch.output() == 1);

    latch.tick(true, false);
    assert(latch.output() == 0);

    std::cout << "[PASS] DLatch tests\n";
}

inline void runDFlipFlopTests() {
    DFlipFlop ff;

    assert(ff.output() == 0);

    ff.setInput(true);
    assert(ff.output() == 0);
    ff.commit();
    assert(ff.output() == 1);

    ff.setInput(false);
    ff.commit();
    assert(ff.output() == 0);

    ff.setInput(true);
    ff.commit();
    assert(ff.output() == 1);

    std::cout << "[PASS] DFlipFlop tests\n";
}

inline void runRegister8Tests() {

    Register8 reg;

    // initial state should be 0
    Byte out = reg.output();
    for (int i = 0; i < 8; ++i)
        assert(out[i] == 0);

    // 1st value
    Byte a = intToByte(0b10101010);
    reg.setInput(true, a);
    reg.commit();

    out = reg.output();
    assert(byteToInt(out) == 0b10101010);

    // 2nd value
    Byte b = intToByte(0b01010101);
    reg.setInput(true, b);
    reg.commit();

    out = reg.output();
    assert(byteToInt(out) == 0b01010101);

    // test HOLD (load = false)
    Byte c = intToByte(0b11111111);
    reg.setInput(false, c);
    reg.commit();

    out = reg.output();
    assert(byteToInt(out) == 0b01010101); // should NOT change

    std::cout << "[PASS] Register8 tests\n";
}

inline void runPCTests() {

    ProgramCounter pc;

    // initial state = 0
    assert(byteToInt(pc.output()) == 0);

    // increment
    pc.tick(ProgramCounter::Mode::Increment);
    assert(byteToInt(pc.output()) == 1);

    pc.tick(ProgramCounter::Mode::Increment);
    assert(byteToInt(pc.output()) == 2);

    // jump
    pc.tick(
        ProgramCounter::Mode::Load,
        intToByte(100)
    );
    assert(byteToInt(pc.output()) == 100);

    // continue incrementing
    pc.tick(ProgramCounter::Mode::Increment);
    assert(byteToInt(pc.output()) == 101);

    //hold test
    pc.tick(ProgramCounter::Mode::Hold);
    assert(byteToInt(pc.output()) == 101);

    //overflow test
    pc.tick(
    ProgramCounter::Mode::Load,
    intToByte(255)
    );
    assert(byteToInt(pc.output()) == 255);

    pc.tick(ProgramCounter::Mode::Increment);
    assert(byteToInt(pc.output()) == 0);

    std::cout << "[PASS] PC tests\n";
}

inline void runAllTests() {

    runGateTests();
    runHalfAdderTests();
    runFullAdderTests();
    runAdd8Tests();
    runMUXTests();
    runDLatchTests();
    runDFlipFlopTests();
    runRegister8Tests();
    runPCTests();

    std::cout << "\n=== ALL TESTS PASSED ===\n";
}