#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>

typedef std::unordered_map<char, std::vector<char>> HuffmanCodes;

/**
 * @brief Struct containing necessary data for min heap node.
 */
struct MinHeapNode {
	char data;
	int freq;
	MinHeapNode *left, *right;

    MinHeapNode(char data_, int freq_);

    bool operator<(MinHeapNode& node);

    bool operator>(MinHeapNode& node);
};

/**
 * @brief Class with implementation of min heap.
 */
class MinHeap {
	std::vector<MinHeapNode*> array;

public:
    /**
     * @brief Map containing codes for every character.
     */
    HuffmanCodes codes;

    /**
     * @brief Constructor for MinHeap class.
     * @param capacity_ Maximum number of elements in min heap.
     */
    MinHeap(int capacity_);

    /**
     * @brief Calculates index of parent node.
     * @param i Input node.
     * @return Index in array of parent node.
     */
    int parent(int i);

    /**
     * @brief Calculates index of left child.
     * @param i Input node.
     * @return Index in array of left node.
     */
    int leftChild(int i);
     
    /**
     * @brief Calculates index of right child.
     * @param i Input node.
     * @return Index in array of right node.
     */
    int rightChild(int i);

    /**
     * @brief Ensures min heap properties for every node above passed index.
     * @param i Index of input node.
     */
    void minHeapify(int idx);

    /**
     * @brief Gets root of min heap.
     * @return Return pointer to root node of min heap.
     */
    MinHeapNode* extractMin();

    /**
     * @brief Inserts new node to min heap.
     * @param minHeapNode Input node.
     */
    void insert(MinHeapNode* minHeapNode);

    /**
     * @brief Builds min heap from private array.
     */
    void build();

    /**
     * @brief Adds new node to private array (it doesn't build min heap).
     * @param inode Input node.
     */
    void add(MinHeapNode* node);

    /**
     * @brief Returns size of min heap.
     * @return Size of min heap.
     */
    int getSize();

    /**
     * @brief Generates huffman codes from min heap with characters to inside variable huffmanCodes which can be later accessed.
     * @param node Root node of huffman tree.
     * @param currCode Empty vector for chars. It is later recursively used to generate codes.
     */
    void generateCodes(MinHeapNode* node, std::vector<char> currCode);
};