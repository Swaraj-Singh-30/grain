#include <iostream>
#include "logic.h"
#include "testing.h"

using namespace std;
enum class Signal { LOW = 0, HIGH = 1 };

// class Wire {
// public:
//     Signal state = Signal::LOW;

//     void set(Signal s) {
//         state = s;
//     }

//     Signal read() const {
//         return state;
//     }
// };

int main() {
    // Wire w;
    // w.set(Signal::HIGH);

    // if (w.read() == Signal::HIGH) {
    //     cout << "HIGH\n";
    // }

    runAllTests();
    return 0;
}
