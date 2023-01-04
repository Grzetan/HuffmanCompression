#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include "minHeap.h"

struct Args{
    std::string input, output, dict;
    bool compression;
};

Args parseArgs(int argc, char* argv[]);

MinHeap* buildHuffmanTreeFromText(std::ifstream& input_file);

void writeDictFile(std::ofstream& dict_file, MinHeap* huffmanTree);

void compress(std::ifstream& input_file, std::ofstream& output_file, MinHeap* huffmanTree);

MinHeapNode* buildHuffmanTreeFromDict(std::ifstream& dict_file);

void decompress(std::ifstream& input_file, std::ofstream& output_file, MinHeapNode* root);
