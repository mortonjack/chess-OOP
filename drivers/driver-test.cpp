#include "driver.h"
#include "bishoptest.h"
#include "rooktest.h"
#include "knighttest.h"
#include "pawntest.h"
#include "kingtest.h"
#include "queentest.h"
#include "capturetest.h"
#include "collisiontest.h"
#include "checktest.h"
#include "checkmatetest.h"
#include "movenodetest.h"
#include "drawtest.h"

int main() {
    driver tests(12);

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
    queentest case6;
    tests.addCase(&case6);

    // Mechanics tests
    capturetest case7;
    tests.addCase(&case7);
    collisiontest case8;
    tests.addCase(&case8);
    checktest case9;
    tests.addCase(&case9);
    checkmatetest case10;
    tests.addCase(&case10);
    movenodetest case11;
    tests.addCase(&case11);
    drawtest case12;
    tests.addCase(&case12);

    tests.runTests();
    return 0;
}