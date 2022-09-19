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

        virtual bool runTests(bool display) = 0;
};

#endif//TESTCASE_H