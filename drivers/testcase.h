#ifndef TESTCASE_H
#define TESTCASE_H
#include <string>
using namespace std;

class testcase {
    protected:
        int _length;
        string _passMessage;
        string _failMessage;
    public:
        testcase();
        testcase(int length);

        virtual bool runTests(bool display) = 0;
        virtual string getMessage(bool pass) = 0;
};

#endif//TESTCASE_H