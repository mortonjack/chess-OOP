#include "driver.h"
#include "bishoptest.h"
#include "rooktest.h"
#include "knighttest.h"
#include <iostream>
using namespace std;

int main() {
    driver tests;
    bishoptest case1;
    rooktest case2;
    knighttest case3;
    tests.addCase(&case1);
    tests.addCase(&case2);
    tests.addCase(&case3);
    tests.runTests();
    return 0;
}