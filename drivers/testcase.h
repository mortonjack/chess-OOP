#ifndef TESTCASE_H
#define TESTCASE_H
#include <string>
using namespace std;

class testcase {
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
        ~testcase();
};

#endif//TESTCASE_H