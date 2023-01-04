#include <iostream>
#include <fstream>
#include <map>
#include "minHeap.h"
#include "utils.h"

int main(int argc, char* argv[]){
    Args args = parseArgs(argc, argv);

    std::ifstream input_file(args.input);
    std::ofstream output_file(args.output);
    if (!input_file.is_open() || !output_file.is_open()) {
        throw std::runtime_error("Cannot open files");
    }

    if(args.compression){
        MinHeap* huffmanTree = buildHuffmanTreeFromText(input_file);

        std::ofstream dict_file("dict.txt");

        writeDictFile(dict_file, huffmanTree);

        compress(input_file, output_file, huffmanTree);
    }else{
        std::ifstream dict_file(args.dict);
        if (!dict_file.is_open()) {
            throw std::runtime_error("Cannot open dict file");
        }

        MinHeapNode* root = buildHuffmanTreeFromDict(dict_file);

        decompress(input_file, output_file, root);
    }

    input_file.close();
    output_file.close();

    return 0;
}