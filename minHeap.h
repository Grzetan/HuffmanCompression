#pragma once
#include <vector>

struct HeapNode{
    char c;
    int freq;

    bool operator>(HeapNode& node) const;
    bool operator<(HeapNode& node) const;
};

class MinHeap{
    std::vector<HeapNode> arr;

    // Return parent
    static int parentNode(int i);

    // Return left child
    static int leftChild(int i);

    // Return right child
    static int rightChild(int i);

public:
    // Traverse down
    void traverseDown(int i);

    // Traverse up
    void traverseUp(int i);

    // Insert
    void insert(HeapNode node);

    // Pop
    void pop();

    // Get top most elem
    HeapNode top();
};