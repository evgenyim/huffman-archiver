#ifndef HW_03_HUFFMAN_H
#define HW_03_HUFFMAN_H

#include <queue>
#include <unordered_map>
#include <fstream>
#include <cstring>
#include <iostream>
#include <memory>

class TreeNode {
public:
    TreeNode();
    TreeNode(int w, char c);
    TreeNode(const std::shared_ptr<TreeNode>& n1, const std::shared_ptr<TreeNode> &n2);
    bool operator>(const TreeNode &node) const;
    std::shared_ptr<TreeNode>& get_left();
    std::shared_ptr<TreeNode>& get_right();
    char get_char();
    size_t get_w();
private:
    size_t _w;
    char _c;
    std::shared_ptr<TreeNode> left, right;
};

class Compare {
public:
    bool operator() (std::shared_ptr<TreeNode> &n1, std::shared_ptr<TreeNode> &n2) {
        return *n1.get() > *n2.get();
    }
};

class HuffTree {
public:
    HuffTree();
    void build(std::priority_queue<std::shared_ptr<TreeNode>, std::vector<std::shared_ptr<TreeNode>>, Compare> &tree);
    void get_code(TreeNode &cur_node, std::vector<bool> &cur_code);
    void gen_codes();
    void encode(std::vector<char> &input, std::vector<char> &ret);
    void decode(std::vector<char> &input, std::vector<char> &ret);
    std::size_t& get_sz();
    std::shared_ptr<TreeNode>& get_root();
    std::unordered_map<char, std::vector<bool>>& get_codes();

private:
    std::shared_ptr<TreeNode> root, cur_node;
    std::size_t _sz;
    std::unordered_map<char, std::vector<bool>> codes;
};


class HuffException {
private:
    std::string message;
public:
    HuffException(const char* text) {
        message = text;
    }
    std::string get() {
        return message;
    }
};

#endif //HW_03_HUFFMAN_H
