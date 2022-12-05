#include "minHeap.h"

bool HeapNode::operator<(HeapNode& node) const{
    return freq < node.freq;
}

bool HeapNode::operator>(HeapNode& node) const {
    return freq > node.freq;
}

int MinHeap::parentNode(int i){
    return (i - 1) / 2;
}

int MinHeap::leftChild(int i){
    return 2*i + 1;
}

int MinHeap::rightChild(int i){
    return 2*i + 2;
}

void MinHeap::traverseDown(int i){
    int left = leftChild(i);
    int right = rightChild(i);

    int largest = i;

    if(left < arr.size() && arr[left] > arr[i]){
        largest = left;
    }
    
    if(right < arr.size() && arr[right] > arr[i]){
        largest = right;
    }

    if(largest != i){
        std::swap(arr[i], arr[largest]);
        traverseDown(largest);
    }
}

void MinHeap::traverseUp(int i){
    int parent = parentNode(i);
    if(arr[i] < arr[parent]){
        std::swap(arr[i], arr[parent]);
        traverseUp(parent);
    }
}

void MinHeap::insert(HeapNode node){
    arr.push_back(node);
    traverseUp(arr.size() - 1);
}

void MinHeap::pop(){
    arr[0] = arr.back();
    arr.pop_back();
    traverseDown(0);
}

HeapNode MinHeap::top(){
    return arr[0];
}