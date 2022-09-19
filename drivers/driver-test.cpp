#include "driver.h"
#include "bishoptest.h"
#include "rooktest.h"
#include <iostream>
using namespace std;

int main() {
    driver tests;
    bishoptest case1;
    rooktest case2;
    tests.addCase(&case1);
    tests.addCase(&case2);
    tests.runTests();
    return 0;
}