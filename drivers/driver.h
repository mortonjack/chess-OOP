#ifndef DRIVER_H
#define DRIVER_H

#include "testcase.h"

class driver {
    protected:
        int _maxLength;
        int _length;
        testcase** _cases;
        bool * _results;
    public:
        driver();
        driver(int length);
        ~driver();

        void addCase(testcase* newCase);
        void runTests();
};

#endif//DRIVER_H