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
        string getMessage(bool pass);
};

#endif//TESTCASE_H