#include "include/driver.h"
#include <iostream>
using namespace std;

int main() {
    driver tests;
    testcase case1;
    testcase case2;
    tests.addCase(case1);
    tests.addCase(case2);
    tests.runTests();
    return 0;
}