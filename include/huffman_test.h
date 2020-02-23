#ifndef HW_03_HUFFMAN_TEST_H
#define HW_03_HUFFMAN_TEST_H

#include "autotest.h"

class HuffTest: public AutoTest {
public:
    void TestTreeNodeConst();
    void TestOperator();
    void TestBuild();
    void TestGenCodes();
    void TestTreeEncode();
    void TestEncodeOneSymbol();
    void TestTreeDecode();
    void TestEncodeDecode();
    void runAllTests();
};

#endif //HW_03_HUFFMAN_TEST_H
