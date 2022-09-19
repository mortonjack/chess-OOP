#ifndef TESTCASE_H
#define TESTCASE_H

class testcase {
    protected:
        int _length;
        bool* _results;
    public:
        testcase();
        testcase(int length);
        ~testcase();

        //virtual bool runTests() = 0;
        bool runTests();
};

#endif//TESTCASE_H