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

    std::unordered_map<char, int> frequencies = {};
    char byte;
    int char_num = 0;
    while (input_file.get(byte)) {
        frequencies[byte]++;
        char_num++;
    }
 
    input_file.close();

    MinHeap huffmanTree(frequencies.size());

    // Add frequencies to huffman tree
    for(auto it = frequencies.cbegin(); it != frequencies.cend(); ++it){
        MinHeapNode* node = new MinHeapNode(it->first, it->second);
        huffmanTree.insert(node);
    }

    // huffmanTree.build();

    // while(huffmanTree.getSize() > 0){
    //     MinHeapNode* node = huffmanTree.extractMin();
    //     std::cout << node->data << ", " << node->freq << std::endl;
    // }

    while(huffmanTree.getSize() != 1){

        MinHeapNode* left = huffmanTree.extractMin();
        MinHeapNode* right = huffmanTree.extractMin();

        MinHeapNode* newNode = new MinHeapNode(NULL, left->freq+right->freq);
        newNode->left = left;
        newNode->right = right;
        huffmanTree.insert(newNode);
    }

    MinHeapNode* root = huffmanTree.extractMin();
    huffmanTree.generateCodes(root, {});

    for(auto it = huffmanTree.codes.begin(); it != huffmanTree.codes.end(); it++){
        std::cout << (*it).first << ": ";
        for(auto& c : (*it).second){
            std::cout << c;
        }
        std::cout << std::endl;
    }

    return 0;
}