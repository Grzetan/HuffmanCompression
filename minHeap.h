#pragma once
#include <vector>
#include <iostream>

struct HeapNode{
    char c;
    int freq;

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

    // Is empty
    bool empty();

    // Get top most elem
    HeapNode top();
};