#include "SaveTest.h"
#include "../include/Game.hpp"
#include <iostream>
using std::cout;
using std::endl;

SaveTest::SaveTest() {
    this->_length = 2;
    this->_failMessage = "Save test failed";
    this->_passMessage = "Save test succeeded";
    initialiseResults();
}

bool SaveTest::directTest(bool display) {
    bool success = false;

    // Initialise objects

    // Place pieces

    // Make moves

    // Save game state
    State savestate();

    // Destroy existing objects


    // Load game state


    return success;
}

bool SaveTest::gameTest(bool display) {
    // Tests game.hpp saves/loads correctly
    bool success = true;

    return success;
}

bool SaveTest::runTests(bool display) {
    _results[0] = directTest(display && !_results[0]);
    _results[1] = gameTest(display && !_results[1]);

    return result();
}