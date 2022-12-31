#include <iostream>
#include <fstream>
#include <map>
#include "minHeap.h"

int main(int argc, char* argv[]){
    std::string input;
    std::string output;
    std::string dict;
    bool compression;

    for(int i=1; i<argc; i++){
        std::string val = argv[i];
        if(val == "-i"){
            if(i == argc-1) throw std::runtime_error("Input not provided");
            input = argv[i+1];
        }else if(val == "-o"){
            if(i == argc-1) throw std::runtime_error("Output not provided");
            output = argv[i+1];
        }else if(val == "-s"){
            if(i == argc-1) throw std::runtime_error("Output not provided");
            dict = argv[i+1];
        }else if(val == "-t"){
            if(i == argc-1) throw std::runtime_error("Output not provided");
            std::string mode = argv[i+1];
            if(mode != "k" && mode != "d") throw std::runtime_error("Wrong mode");
            compression = mode == "k";
        }
    }

    std::ifstream input_file(input);
    std::ofstream output_file(output);
    if (!input_file.is_open() || !output_file.is_open()) {
        throw std::runtime_error("Cannot open input file");
    }

    if(compression){
        std::unordered_map<char, int> frequencies = {};
        char byte;
        while (input_file.get(byte)) {
            frequencies[byte]++;
        }
    
        MinHeap huffmanTree(frequencies.size());

        // Add frequencies to huffman tree
        for(auto it = frequencies.cbegin(); it != frequencies.cend(); ++it){
            MinHeapNode* node = new MinHeapNode(it->first, it->second);
            huffmanTree.insert(node);
        }

        // Print out generated tree
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

        std::ofstream dict_file("dict.txt");

        // Save generated codes
        for(auto it = huffmanTree.codes.begin(); it != huffmanTree.codes.end(); it++){
            dict_file << (*it).first << " ";
            for(auto& c : (*it).second){
                dict_file << c;
            }
            dict_file << std::endl;
        }

        // Encode input file using generated codes
        input_file.clear();
        input_file.seekg(0, input_file.beg);
        while (input_file.get(byte)) {
            for(auto& bit : huffmanTree.codes[byte]){
                output_file << bit;
            }
        }
    }else{
        std::ifstream dict_file(dict);
        if (!dict_file.is_open()) {
            throw std::runtime_error("Cannot open dict file");
        }

        // Read dict into map
        std::unordered_map<char, std::string> huffmanCodes = {};
        char c;
        std::string code;
        while(dict_file >> c >> code){
            huffmanCodes[c] = code;
        }

        // Decompress input file into output file
        char byte;

    }

    input_file.close();
    output_file.close();

    return 0;
}