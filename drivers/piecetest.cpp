#include "piecetest.h"

bool piecetest::runTests(bool display) {
    bool success = true;

    success = success && movementTest(display);
    success = success && captureTest(display);
    success = success && checkTest(display);

    return success;
}