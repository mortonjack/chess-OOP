#ifndef TESTCASE_H
#define TESTCASE_H
#include <string>
using std::string;

class TestCase {
    protected:
        // Stores the number of tests to run
        int _length;

        // Array which stores the past test results
        bool * _results;

        // Strings to output to stdout when the test passes/fails
        string _passMessage;
        string _failMessage;

    public:
        // Initialises results array to false
        void initialiseResults();

        // Returns relevant message based off input boolean value
        string getMessage(bool pass);

        // Returns true if all tests passed. Else returns false
        bool result();

        // Run tests.
        // Display outputs previously failed tests to stdout.
        virtual bool runTests(bool display) = 0;

        // Frees results array
        ~TestCase();
};

#endif//TESTCASE_H