#include "Driver.h"
#include "BishopTest.h"
#include "RookTest.h"
#include "KnightTest.h"
#include "PawnTest.h"
#include "KingTest.h"
#include "QueenTest.h"
#include "CaptureTest.h"
#include "CollisionTest.h"
#include "CheckTest.h"
#include "CheckmateTest.h"
#include "MoveNodeTest.h"
#include "DrawTest.h"

int main() {
    Driver tests(12);

    // Piece tests
    BishopTest case1;
    tests.addCase(&case1);
    RookTest case2;
    tests.addCase(&case2);
    KnightTest case3;
    tests.addCase(&case3);
    PawnTest case4;
    tests.addCase(&case4);
    KingTest case5;
    tests.addCase(&case5);
    QueenTest case6;
    tests.addCase(&case6);

    // Mechanics tests
    CaptureTest case7;
    tests.addCase(&case7);
    CollisionTest case8;
    tests.addCase(&case8);
    CheckTest case9;
    tests.addCase(&case9);
    CheckmateTest case10;
    tests.addCase(&case10);
    MoveNodeTest case11;
    tests.addCase(&case11);
    DrawTest case12;
    tests.addCase(&case12);

    tests.runTests();
    return 0;
}