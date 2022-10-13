#ifndef TESTCASE_H
#define TESTCASE_H
#include <string>
using namespace std;

class TestCase {
    protected:
        int _length;
        bool * _results;
        string _passMessage;
        string _failMessage;
    public:
        void initialiseResults();
        virtual bool runTests(bool display) = 0;
        string getMessage(bool pass);
        bool result();
        ~TestCase();
};

#endif//TESTCASE_H