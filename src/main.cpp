#include <iostream>
#include <fstream>
#include <cstring>
#include "huffman.h"
#include "huffman_archiver.h"

int main(int argc, char *argv[]) {
    HuffArchiver archiver;
    std::ifstream in;
    std::ofstream out;
    bool flag = false, encode = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            in.open(argv[++i]);
        } else if (strcmp(argv[i], "-o") == 0) {
            out.open(argv[++i]);
        } else if (strcmp(argv[i], "-c") == 0) {
            flag = true;
            encode = true;
        } else if (strcmp(argv[i], "-u") == 0) {
            flag = true;
            encode = false;
        } else {
            std::cerr << "Wrong Input" << std::endl;
            return 0;
        }
    }
    if (flag) {
        if (encode) {
            try {
                archiver.encode(in, out);
            } catch (HuffException &e) {
                std::cerr << e.get();
                exit(0);
            }
        } else try {
            archiver.decode(in, out);
        } catch (HuffException &e) {
            std::cerr << e.get();
            exit(0);
        }
    }
    return 0;
}