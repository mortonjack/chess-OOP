#ifndef DRIVER_H
#define DRIVER_H

#include "TestCase.h"

class Driver {
    protected:
        int _maxLength;
        int _length;
        TestCase** _cases;
        bool * _results;
    public:
        Driver();
        Driver(int length);
        ~Driver();

        void addCase(TestCase* newCase);
        void runTests();
};

#endif//DRIVER_H