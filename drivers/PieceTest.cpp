#include "PieceTest.h"

bool PieceTest::runTests(bool display) {

    _results[0] = movementTest(display && !_results[0]);
    _results[1] = CaptureTest(display && !_results[1]);
    _results[2] = checkTest(display && !_results[2]);

    return result();
}