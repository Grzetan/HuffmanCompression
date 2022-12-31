#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>

typedef std::unordered_map<char, std::vector<char>> HuffmanCodes;

struct MinHeapNode {
	char data;
	int freq;
	MinHeapNode *left, *right;

    MinHeapNode(char data_, int freq_);

    bool operator<(MinHeapNode& node);

    bool operator>(MinHeapNode& node);
};

class MinHeap {
	std::vector<MinHeapNode*> array;

public:
    HuffmanCodes codes;

    MinHeap(int capacity_);

    int parent(int i);

    int leftChild(int i);
     
    int rightChild(int i);

    void minHeapify(int idx);

    MinHeapNode* extractMin();

    void insert(MinHeapNode* minHeapNode);

    void build();

    void add(MinHeapNode* node);

    int getSize();

    void generateCodes(MinHeapNode* node, std::vector<char> currCode);
};