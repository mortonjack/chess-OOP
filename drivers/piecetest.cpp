#include "piecetest.h"

bool piecetest::runTests(bool display) {

    _results[0] = movementTest(display && !_results[0]);
    _results[1] = captureTest(display && !_results[0]);
    _results[2] = checkTest(display && !_results[0]);

    return result();
}