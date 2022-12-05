#include <iostream>
#include <fstream>
#include <map>
#include "minHeap.h"

int main(int argc, char* argv[]){
    std::string input;
    std::string output;

    for(int i=1; i<argc; i++){
        std::string val = argv[i];
        if(val == "-i"){
            if(i == argc-1) throw std::runtime_error("Input not provided");
            input = argv[i+1];
        }else if(val == "-o"){
            if(i == argc-1) throw std::runtime_error("Output not provided");
            output = argv[i+1];
        }
    }

    std::ifstream input_file(input);
    if (!input_file.is_open()) {
        throw std::runtime_error("Cannot open input file");
    }

    std::map<char, int> frequencies = {};
    char byte;
    while (input_file.get(byte)) {
        frequencies[byte]++;
    }

    input_file.close();

    MinHeap huffmanTree;

    // Add frequencies to huffman tree
    for(auto it = frequencies.cbegin(); it != frequencies.cend(); ++it){
        HeapNode node = {it->first, it->second};
        huffmanTree.insert(node);
    }


    while(!huffmanTree.empty()){
        std::cout << huffmanTree.top() << std::endl;
        huffmanTree.pop();
    }


    return 0;
}