#include "driver.h"
#include "bishoptest.h"
#include "rooktest.h"
#include "knighttest.h"
#include "pawntest.h"
#include "kingtest.h"
#include <iostream>
using namespace std;

int main() {
    driver tests(6);

    // Piece tests
    bishoptest case1;
    tests.addCase(&case1);
    rooktest case2;
    tests.addCase(&case2);
    knighttest case3;
    tests.addCase(&case3);
    pawntest case4;
    tests.addCase(&case4);
    kingtest case5;
    tests.addCase(&case5);

    tests.runTests();
    return 0;
}