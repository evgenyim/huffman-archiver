#ifndef HW_03_HUFFMAN_ARCHIVER_H
#define HW_03_HUFFMAN_ARCHIVER_H

#include <fstream>
#include <vector>
#include <unordered_map>
#include "huffman.h"

class HuffArchiver {
public:
    void encode(std::ifstream &in, std::ofstream &out);
    void decode(std::ifstream &in, std::ofstream &out);
    void decode_from_file(std::ifstream &in, std::ofstream &out, HuffTree &tree);
    void write_to_file(std::vector<char> &input, std::unordered_map<char, int> &chars, std::ofstream &of, HuffTree &tree);
};


#endif //HW_03_HUFFMAN_ARCHIVER_H
