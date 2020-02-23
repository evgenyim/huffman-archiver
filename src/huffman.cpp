#include <memory>

#include "huffman.h"

TreeNode::TreeNode() {
    _w = _c = 0;
    left = nullptr;
    right = nullptr;
}

TreeNode::TreeNode(const std::shared_ptr<TreeNode> &n1, const std::shared_ptr<TreeNode> &n2) {
    _w = 0;
    if (n1 != nullptr) {
        _w += n1->get_w();
    }if (n2 != nullptr) {
        _w += n2->get_w();
    }
    left = n1;
    right = n2;
    _c = '\0';
}

TreeNode::TreeNode(int w, char c) {
    _w = w;
    _c = c;
    left = nullptr;
    right = nullptr;
}

bool TreeNode::operator>(const TreeNode &node) const {
    return _w > node._w;
}

std::shared_ptr<TreeNode>& TreeNode::get_left() {
    return left;
}

std::shared_ptr<TreeNode>& TreeNode::get_right() {
    return right;
}

char TreeNode::get_char() {
    return _c;
}

size_t TreeNode::get_w() {
    return _w;
}

HuffTree::HuffTree() {
    root = nullptr;
    cur_node = nullptr;
    _sz = 0;
}

void HuffTree::build(std::priority_queue<std::shared_ptr<TreeNode>, std::vector<std::shared_ptr<TreeNode>>, Compare> &tree) {
    if (tree.size() == 1) {
        auto n1 = tree.top();
        auto new_node = std::make_shared<TreeNode>(n1, nullptr);
        root = new_node;
        return;
    }
    while (tree.size() > 1) {
        auto n1 = tree.top();
        tree.pop();
        auto n2 = tree.top();
        tree.pop();
        auto new_node = std::make_shared<TreeNode>(n1, n2);
        tree.push(new_node);
    }
    if (tree.empty()) throw HuffException("Can't build tree");
    root = tree.top();
}

void HuffTree::get_code(TreeNode &node, std::vector<bool> &cur_code) {
    if (node.get_left() == nullptr and node.get_right() == nullptr) {
        codes.insert({node.get_char(), cur_code});
    }
    if (node.get_left() != nullptr) {
        cur_code.push_back(false);
        get_code(*node.get_left(), cur_code);
    }
    if (node.get_right() != nullptr) {
        cur_code.push_back(true);
        get_code(*node.get_right(), cur_code);
    }
    cur_code.pop_back();
}

void HuffTree::gen_codes() {
    std::vector<bool> code;
    if (root == nullptr) throw HuffException("Can't generate codes");
    get_code(*root, code);
}

void HuffTree::encode(std::vector<char> &input, std::vector<char> &ret) {
    char buf = 0;
    int cnt = 0;
    for (char c : input) {
        if(codes[c].empty()) throw HuffException("Can't encode, bad codes list");
        std::vector<bool> code = codes[c];
        for (auto b : code) {
            buf |= b << 7 - cnt;
            cnt++;
            if (cnt == 8) {
                cnt = 0;
                ret.push_back(buf);
                buf = 0;
            }
        }
    }
    if (cnt > 0 and cnt < 8) {
        while (cnt < 8) {
            buf |= 0 << (7 - cnt);
            cnt++;
        }
        ret.push_back(buf);
    }
}

void HuffTree::decode(std::vector<char> &input, std::vector<char> &ret) {
    cur_node = root;
    if (input.empty()) throw HuffException("Nothing to decode");
    if (root == nullptr) throw HuffException("Bad tree to decode");
    int cnt = 0;
    char b = input[0];
    for (int i = 0; i < input.size();) {
        bool bl = b & (1 << (7 - cnt));
        if (bl) {
            cur_node = cur_node->get_right();
        } else {
            cur_node = cur_node->get_left();
        }
        if (cur_node->get_left() == nullptr and cur_node->get_right() == nullptr) {
            ret.push_back(cur_node->get_char());
            cur_node = root;
        }
        if (ret.size() == _sz) break;
        cnt++;
        if (cnt == 8) {
            cnt = 0;
            b = input[++i];
        }
    }
}

std::size_t& HuffTree::get_sz() {
    return _sz;
}

std::shared_ptr<TreeNode>& HuffTree::get_root() {
    return root;
}

std::unordered_map<char, std::vector<bool>>& HuffTree::get_codes() {
    return codes;
}
