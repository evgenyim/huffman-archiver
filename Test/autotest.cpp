#include <iostream>
#include "autotest.h"

AutoTest::AutoTest() {
    totalNum = 0;
    failedNum = 0;
}

void AutoTest::showFinalResult() {
    if (failedNum == 0) {
        std::cout << "All tests passed" << std::endl;
    } else {
        std::cout << "Failed " << failedNum << " of " << totalNum << " tests" << std::endl;
    }
}

void AutoTest::check(bool expr, const char *func, const char *filename, size_t lineNum) {
    totalNum++;
    if (!expr) {
        failedNum++;
        std::cout << "Test failed: " << func << " in " << filename << ":" << lineNum << std::endl;
    }
}