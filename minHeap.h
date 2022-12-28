#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>

struct HeapNode{
    char c;
    int freq;
    bool isChar = false;

    bool operator>(HeapNode& node) const;
    bool operator<(HeapNode& node) const;
    friend std::ostream &operator<<(std::ostream &output, const HeapNode &D ) { 
        output << D.c << ": " << D.freq;
        return output;            
    }
};

class MinHeap{
    std::vector<HeapNode> arr;

    // Return parent
    int parentNode(int i);

    // Return left child
    int leftChild(int i);

    // Return right child
    int rightChild(int i);

public:
    std::unordered_map<char, std::vector<char>> codes;

    // Traverse down
    void traverseDown(int i);

    // Traverse up
    void traverseUp(int i);

    // Insert
    void insert(HeapNode node);

    // Pop
    void pop();

    // Is empty
    bool empty();

    // Checks if node is a leaf
    bool isLeaf(int i);

    // Get top most elem
    HeapNode top();

    // Generate huffman codes
    void generateCodes(int root, std::vector<char> currCode);

};