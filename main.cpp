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
        throw std::runtime_error("Cannot open files");
    }

    if(compression){
        std::unordered_map<char, int> frequencies = {};
        char byte;
        while (input_file.get(byte)) {
            frequencies[byte]++;
        }
    
        // Add EOF token
        frequencies['\0'] = 1;

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
            std::string key;
            key.push_back((*it).first);
            if(key == " ") key = "space";
            else if(key == "\n") key = "newline";
            else if((*it).first == '\0') key = "eof";
            dict_file << key << " ";
            for(auto& c : (*it).second){
                dict_file << c;
            }
            dict_file << std::endl;
        }

        input_file.clear();
        input_file.seekg(0, input_file.beg);

        char workingByte = 0;
        int emptySpace = 7; // Bool is 8 bits

        while (!input_file.eof()) {
            input_file.get(byte);
            if(input_file.eof()){
                byte = '\0';
            }

            for(auto& bit : huffmanTree.codes[byte]){
                if(bit == '1'){
                    workingByte += 1;
                }
                std::cout << bit;

                if(!emptySpace--){
                    emptySpace = 7;
                    output_file << workingByte;
                    workingByte = 0;
                }

                workingByte = workingByte << 1;
            }
        }

        // If there is still something in working byte, write it
        if(emptySpace < 7)
            output_file << workingByte;

    }else{
        std::ifstream dict_file(dict);
        if (!dict_file.is_open()) {
            throw std::runtime_error("Cannot open dict file");
        }

        // Read dict into map
        std::map<std::string, char> huffmanCodes = {};
        std::string c;
        std::string code;
        while(dict_file >> c >> code){
            char ch = c[0];
            if(c == "space") ch = ' ';
            else if(c == "newline") ch = '\n';
            else if(c == "eof") ch = '\0';
            huffmanCodes[code] = ch;
        }

        // Create huffman tree from dict
        MinHeapNode* root = new MinHeapNode('~', 0);

        for(auto it = huffmanCodes.begin(); it != huffmanCodes.end(); it++){
            MinHeapNode* curr = root;
            for(auto& c : (*it).first){
                if(c == '0'){
                    if(curr->left){
                        curr = curr->left;
                        continue;
                    }

                    MinHeapNode* child = new MinHeapNode('~', 0);
                    curr->left = child;
                    curr = curr->left;
                }else if(c == '1'){
                    if(curr->right){
                        curr = curr->right;
                        continue;
                    }

                    MinHeapNode* child = new MinHeapNode('~', 0);
                    curr->right = child;
                    curr = curr->right;
                }
            }

            curr->data = (*it).second;
        }

        // Decompress input file into output file
        char byte;
        MinHeapNode* curr = root;

        bool eof = false;

        while (input_file.get(byte) && !eof) {
            for (int i = 7; i >= 0; i--){
                char singleBit = ((byte >> i) & 1);

                std::cout << (singleBit == 1);

                if(singleBit == 0){
                    curr = curr->left;
                }else{
                    curr = curr->right;
                }

                if(curr->data == '\0'){
                    std::cout << "XD";
                    eof = true;
                    break;
                }

                if(!curr->left && !curr->right){
                    output_file << curr->data;
                    curr = root;
                }
            }
        }
    }

    input_file.close();
    output_file.close();

    return 0;
}