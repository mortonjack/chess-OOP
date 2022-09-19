#include "driver.h"
#include "bishoptest.h"
#include <iostream>
using namespace std;

int main() {
    driver tests;
    bishoptest case1;
    tests.addCase(&case1);
    tests.runTests();
    return 0;
}