#include "huffman_archiver.h"
#include "huffman.h"
#define SYMBOL_SIZE_IN_TABLE 5

void HuffArchiver::encode(std::ifstream &in, std::ofstream &out) {
    if (!in.is_open() or !out.is_open()) throw HuffException("File is not open");
    std::unordered_map<char, int> chars;
    std::vector<char> input;
    char tmp = in.get();

    while (!in.eof()) {
        chars[tmp]++;
        input.push_back(tmp);
        tmp = in.get();
    }

    std::cout << input.size() << std::endl;

    if (input.empty()) {
        std::cout << 0 << std::endl;
        std::cout << 0 << std::endl;
        return;
    }

    std::priority_queue<std::shared_ptr<TreeNode>, std::vector<std::shared_ptr<TreeNode>>, Compare> q;
    for (auto i : chars) {
        auto node = std::make_shared<TreeNode>(i.second, i.first);
        q.push(node);
    }
    HuffTree tree;

    try {
        tree.build(q);
        tree.gen_codes();
    } catch (HuffException &e) {
        std::cerr << e.get();
        exit(0);
    }

    write_to_file(input, chars, out, tree);
}


void HuffArchiver::decode(std::ifstream &in, std::ofstream &out) {
    HuffTree tree;
    int sz = 0;
    if (!in.is_open() or !out.is_open()) throw HuffException("File is not open");
    in.read((char *) &sz, sizeof(int));
    std::priority_queue<std::shared_ptr<TreeNode>, std::vector<std::shared_ptr<TreeNode>>, Compare> q;
    for (int i = 0; i < sz; i++) {
        char c;
        in.read(&c, sizeof(char));
        int w;
        in.read((char *) &w, sizeof(int));
        tree.get_sz() += w;
        auto node = std::make_shared<TreeNode>(w, c);
        q.push(node);
    }

    if (q.empty()) {
        std::cout << 0 << std::endl;
        std::cout << 0 << std::endl;
        std::cout << 0 << std::endl;
        return;
    }

    try {
        tree.build(q);
    } catch (HuffException &e) {
        std::cerr << e.get();
        exit(0);
    }

    decode_from_file(in, out, tree);
    std::cout << sz * SYMBOL_SIZE_IN_TABLE + sizeof(int) << std::endl;
}

void HuffArchiver::decode_from_file(std::ifstream &in, std::ofstream &out, HuffTree &tree) {
    std::vector<char> vec, input;
    char c = in.get();
    while (!in.eof()) {
        input.push_back(c);
        c = in.get();
    }

    try {
        tree.decode(input, vec);
    } catch (HuffException &e) {
        std::cerr << e.get();
        exit(0);
    }

    for (char i : vec) {
        out << i;
    }
    out.close();
    std::cout << input.size() << std::endl;
    std::cout << vec.size() << std::endl;
}

void HuffArchiver::write_to_file(std::vector<char> &input, std::unordered_map<char, int> &chars, std::ofstream &of, HuffTree &tree) {
    int sz = chars.size();
    int extra_size = 0;
    of.write((char *) &sz, sizeof(int));
    for (auto i : chars) {
        of.put(i.first);
        int w = i.second;
        extra_size++;
        of.write((char *) &w, sizeof(int));
    }
    extra_size *= SYMBOL_SIZE_IN_TABLE;
    extra_size += sizeof(int);
    std::vector<char> out;

    try {
        tree.encode(input, out);
    } catch (HuffException &e) {
        std::cerr << e.get();
        exit(0);
    }

    for (auto c : out) {
        of.put(c);
    }
    std::cout << out.size() << std::endl;
    std::cout << extra_size << std::endl;
}
