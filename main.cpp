#include <iostream>
#include "logic.h"

using namespace std;
enum class Signal { LOW = 0, HIGH = 1 };

class Wire {
public:
    Signal state = Signal::LOW;

    void set(Signal s) {
        state = s;
    }

    Signal read() const {
        return state;
    }
};

int main() {
    Wire w;
    w.set(Signal::HIGH);

    if (w.read() == Signal::HIGH) {
        cout << "HIGH\n";
    }

    cout << "AND(1,0) = " << AND(true, false) << "\n";
    cout << "OR(1,0)  = " << OR(true, false) << "\n";
    cout << "XOR(1,1) = " << XOR(true, true) << "\n";

    Byte A = {1,0,1,0,0,0,0,0}; // 5 (LSB first)
    Byte B = {1,0,0,0,0,0,0,0}; // 1

    Add8Result result = add8(A, B);

    std::cout << "Sum: ";
    for (int i = 7; i >= 0; i--) {
        std::cout << result.sum[i];
    }
    std::cout << "\nCarry out: " << result.carry_out << "\n";
    return 0;
}
