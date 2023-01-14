#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include "minHeap.h"

/**
 * @brief Custom struct with information extracted from CLI arguments
 */
struct Args{
    std::string input, output, dict;
    bool compression;
};


/**
 * @brief Parse arguments from commend line.
 * @param argc Number of parameters. It should have a length equal to length of second parameter
 * @param argv C-type array of arguments passed through command line.
 * @return Returns custom struct containing parsed arguments.
 */
Args parseArgs(int argc, char* argv[]);

/**
 * @brief First, it builds priority queue from characters and their frequencies, than huffman tree is build.
 * @param input_file File stream (ifstream) with opened file we want to compress.
 * @return Returns a pointer to root node of huffman tree.
 */
MinHeap* buildHuffmanTreeFromText(std::ifstream& input_file);

/**
 * @brief Writes file with pairs of characters from input file and their code in huffman tree.
 * @param dict_file File stream (ofstream) with opened, ready to write, dictionary file.
 * @param huffmanTree Pointer to the root of huffman tree.
 */
void writeDictFile(std::ofstream& dict_file, MinHeap* huffmanTree);

/**
 * @brief Writes compressed input file. It uses bit operators so compressed codes use smallest possible amount of memory.
 * @param input_file File stream (ifstream) with opened file we want to compress.
 * @param output_file File stream (ofstream) with opened file in which we want to write compressed text.
 * @param huffmanTree Pointer to the root of huffman tree.
 */
void compress(std::ifstream& input_file, std::ofstream& output_file, MinHeap* huffmanTree);

/**
 * @brief Builds huffman tree from input dictionary file (created when compressing).
 * @param dict_file File stream (ofstream) with opened, ready to write, dictionary file.
 * @return Returns a pointer to root node of huffman tree.
 */
MinHeapNode* buildHuffmanTreeFromDict(std::ifstream& dict_file);


/**
 * @brief Decompresses input file to output file.
 * @param input_file File stream (ifstream) with opened file with compressed text.
 * @param output_file File stream (ofstream) with opened file in which we want to write decompressed text.
 * @param root Pointer to the root of huffman tree.
 */
void decompress(std::ifstream& input_file, std::ofstream& output_file, MinHeapNode* root);
