#include "bigint.hpp"
#include <iostream>
using namespace std;

int main()
{
    // 1. DISPLAY POSITIVES------------------------------
    bigint pos_val("1234567890123456789012345678965767879797950");
    cout << "\n1. displaying positive value: " << pos_val;
    pos_val.set(45453445);
    cout << "\n1. newly set positive value: " << pos_val << "\n\n";

    // 2. DISPLAY NEGATIVES------------------------------
    bigint neg_val("-123456789012345678901234567896805655687766");
    cout << "2. displaying negative value: " << neg_val << "\n";
    neg_val.set(-45453445);
    cout << "2. newly set negative value: " << neg_val << "\n\n";

    // COMPARE
    bigint test1("123455");
    bigint test2("123455");
    cout << "3. testing values 123455 if they are the same: " << (test1 >= test2) << "\n\n";

    test1.set("232332");
    test2.set(232332);
    cout << "4. testing values 232332 if they are not the same: " << (test1 != test2) << "\n\n";

    // 3. ADDITION---------------------------------------
    // positive and positive
    bigint add1("123456");
    bigint add2("654321");
    cout << "5. Addition (positive + positive): " << (add1 + add2) << "\n\n";

    // positive and negative
    bigint add3("-123456");
    cout << "6. Addition (positive + negative): " << (add1 + add3) << "\n\n";

    // negative and positive
    cout << "7. Addition (negative + positive): " << (add3 + add1) << "\n\n";

    // negative and negative
    bigint add4("-654321");
    cout << "8. Addition (negative + negative): " << (add3 + add4) << "\n\n";

    // 4. SUBTRACTION------------------------------------
    // positive and positive
    cout << "9. Subtraction (positive - positive): " << (add1 - add2) << "\n\n";

    // positive and negative
    cout << "10. Subtraction (positive - negative): " << (add1 - add3) << "\n\n";

    // negative and positive
    cout << "11. Subtraction (negative - positive): " << (add3 - add1) << "\n\n";

    // 5. MULTIPLICATION----------------------------------
    // positive and positive
    cout << "12. Multiplication (positive * positive): " << (add1 * add2) << "\n\n";

    // positive and negative
    cout << "13. Multiplication (positive * negative): " << (add1 * add3) << "\n\n";

    // negative and positive
    cout << "14. Multiplication (negative * positive): " << (add3 * add1) << "\n\n";

    // negative and negative
    cout << "15. Multiplication (negative * negative): " << (add3 * add4) << "\n\n";

    return 0;
}
