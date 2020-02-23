#include "huffman_test.h"
#include "huffman.h"
#define DO_CHECK(EXPR) check(EXPR, __FUNCTION__, __FILE__, __LINE__)

void HuffTest::TestTreeNodeConst() {
    auto n1 = std::make_shared<TreeNode>(10, 's');
    auto n2 = std::make_shared<TreeNode>(15, 'a');
    TreeNode n3(n1, n2);
    DO_CHECK(n3.get_right() == n1 or n3.get_right() == n2);
    DO_CHECK(n3.get_left() == n1 or n3.get_left() == n2);
    DO_CHECK(n3.get_left() != n3.get_right());
}

void HuffTest::TestOperator() {
    TreeNode n1(10, 'd');
    TreeNode n2(20, 'a');
    DO_CHECK(n2 > n1);
}

void HuffTest::TestBuild() {
    auto n1 = std::make_shared<TreeNode>(10, '1');
    auto n2 = std::make_shared<TreeNode>(11, '2');
    auto n3 = std::make_shared<TreeNode>(12, '3');
    std::priority_queue<std::shared_ptr<TreeNode>, std::vector<std::shared_ptr<TreeNode>>, Compare> q;
    q.push(n1), q.push(n2), q.push(n3);
    HuffTree tree;
    tree.build(q);
    DO_CHECK(tree.get_root()->get_w() == 33);
}

void HuffTest::TestGenCodes() {
    auto n1 = std::make_shared<TreeNode>(10, '1');
    auto n2 = std::make_shared<TreeNode>(11, '2');
    auto n3 = std::make_shared<TreeNode>(22, '3');
    std::priority_queue<std::shared_ptr<TreeNode>, std::vector<std::shared_ptr<TreeNode>>, Compare> q;
    q.push(n1), q.push(n2), q.push(n3);
    HuffTree tree;
    tree.build(q);
    std::vector<bool> code;
    tree.gen_codes();
    code = {false, false};
    DO_CHECK(tree.get_codes()['1'] == code);
    code = {false, true};
    DO_CHECK(tree.get_codes()['2'] == code);
    code = {true};
    DO_CHECK(tree.get_codes()['3'] == code);
}

void HuffTest::TestTreeEncode() {
    auto n1 = std::make_shared<TreeNode>(1, '1');
    auto n2 = std::make_shared<TreeNode>(1, '2');
    auto n3 = std::make_shared<TreeNode>(4, '3');
    std::priority_queue<std::shared_ptr<TreeNode>, std::vector<std::shared_ptr<TreeNode>>, Compare> q;
    q.push(n1), q.push(n2), q.push(n3);
    HuffTree tree;
    tree.build(q);
    tree.gen_codes();
    std::vector<char> input = {'1', '2', '3', '3'};
    std::vector<char> ret;
    tree.encode(input, ret);
    DO_CHECK(ret.size() == 1);
}

void HuffTest::TestEncodeOneSymbol() {
    auto n1 = std::make_shared<TreeNode>(9, '1');
    std::priority_queue<std::shared_ptr<TreeNode>, std::vector<std::shared_ptr<TreeNode>>, Compare> q;
    q.push(n1);
    HuffTree tree;
    tree.build(q);
    tree.gen_codes();
    std::vector<char> input = {'1', '1', '1', '1', '1', '1', '1', '1', '1'};
    std::vector<char> ret;
    tree.encode(input, ret);
    DO_CHECK(ret.size() == 2);
}

void HuffTest::TestTreeDecode() {
    auto n1 = std::make_shared<TreeNode>(1, '1');
    auto n2 = std::make_shared<TreeNode>(2, '2');
    auto n3 = std::make_shared<TreeNode>(2, '3');
    std::priority_queue<std::shared_ptr<TreeNode>, std::vector<std::shared_ptr<TreeNode>>, Compare> q;
    q.push(n1), q.push(n2), q.push(n3);
    HuffTree tree;
    tree.build(q);
    tree.gen_codes();
    std::vector<char> ret;
    std::vector<char> in = {'+'};
    std::vector<char> expected = {'3', '3', '1', '1', '2'};
    tree.get_sz() += expected.size();
    tree.decode(in, ret);
    DO_CHECK(ret == expected);
}

void HuffTest::TestEncodeDecode() {
    auto n1 = std::make_shared<TreeNode>(1, 'H');
    auto n2 = std::make_shared<TreeNode>(1, 'e');
    auto n3 = std::make_shared<TreeNode>(3, 'l');
    auto n4 = std::make_shared<TreeNode>(2, 'o');
    auto n5 = std::make_shared<TreeNode>(1, ',');
    auto n6 = std::make_shared<TreeNode>(1, ' ');
    auto n7 = std::make_shared<TreeNode>(1, 'w');
    auto n8 = std::make_shared<TreeNode>(1, 'r');
    auto n9 = std::make_shared<TreeNode>(1, 'd');
    auto n10 = std::make_shared<TreeNode>(1, '!');

    std::priority_queue<std::shared_ptr<TreeNode>, std::vector<std::shared_ptr<TreeNode>>, Compare> q;
    q.push(n1), q.push(n2), q.push(n3), q.push(n4), q.push(n5),
    q.push(n9), q.push(n8), q.push(n7), q.push(n6), q.push(n10);
    HuffTree tree;
    tree.build(q);
    tree.gen_codes();
    std::vector<char> encoded, out;
    std::vector<char> in = {'H', 'e', 'l', 'l', 'o', ',', ' ',
                            'w', 'o', 'r', 'l', 'd', '!'};
    tree.encode(in, encoded);
    tree.get_sz() += in.size();
    tree.decode(encoded, out);
    DO_CHECK(in == out);


}

void HuffTest::runAllTests() {
    TestBuild();
    TestGenCodes();
    TestOperator();
    TestTreeEncode();
    TestTreeNodeConst();
    TestTreeDecode();
    TestEncodeOneSymbol();
    TestEncodeDecode();
}
