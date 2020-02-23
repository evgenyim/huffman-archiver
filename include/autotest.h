#ifndef HW_02_AUTOTEST_H
#define HW_02_AUTOTEST_H
#include <cstddef>

class AutoTest {
protected:
    int failedNum;
    int totalNum;
public:
    AutoTest();
    void check(bool expr, const char *func, const char  *filename, size_t lineNum);
    void showFinalResult();
    virtual void runAllTests() = 0;
};


#endif