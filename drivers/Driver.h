#ifndef DRIVER_H
#define DRIVER_H

#include "TestCase.h"

class Driver {
    private:
        // Stores the maximum capacity of the _cases array
        int _maxLength;
        
        // Stores the current length of the _cases array
        int _length;

        // Stores the testcases to be run
        TestCase** _cases;

        // Stores the results of the testcases
        bool * _results;

    public:
        /* 
         * Constructors
         * Length determines the starting capacity of the _cases array
         * which is dynamically increases as cases are added
         * The default constructor sets this to 1
         */
        Driver();
        Driver(int length);

        // Destructor
        ~Driver();

        // Add case to be tested
        void addCase(TestCase* newCase);

        // Runs tests & outputs results to stdout
        void runTests();
};

#endif//DRIVER_H