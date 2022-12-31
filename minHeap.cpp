#include "minHeap.h"

MinHeapNode::MinHeapNode(char data_, int freq_){
    left = right = NULL;
    data = data_;
    freq = freq_;
}

bool MinHeapNode::operator<(MinHeapNode& node){
    return freq < node.freq;
}

bool MinHeapNode::operator>(MinHeapNode& node){
    return freq > node.freq;
}

MinHeap::MinHeap(int capacity_){
    array = {};
}

int MinHeap::parent(int i){
    return (i-1) / 2;
}

int MinHeap::leftChild(int i){
    return 2 * i + 1;
}

int MinHeap::rightChild(int i){
    return 2 * i + 2;
}

void MinHeap::minHeapify(int idx){
    int smallest = idx;
    int left = leftChild(idx);
    int right = rightChild(idx);

    if (left < array.size() && *(array[left]) < *(array[smallest]))
        smallest = left;

    if (right < array.size() && *(array[right]) < *(array[smallest]))
        smallest = right;

    if (smallest != idx) {
        std::swap(array[smallest], array[idx]);
        minHeapify(smallest);
    }
}

MinHeapNode* MinHeap::extractMin(){
    MinHeapNode* temp = array[0];
    array[0] = array[array.size() - 1];
    array.pop_back();
    
    minHeapify(0);

    return temp;
}

void MinHeap::insert(MinHeapNode* minHeapNode){
    array.push_back(0);
    int i = array.size() - 1;

    while (i && *(minHeapNode) < *(array[parent(i)])) {

        array[i] = array[parent(i)];
        i = parent(i);
    }

    array[i] = minHeapNode;
}

void MinHeap::build(){

    int n = array.size() - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(i);
}

void MinHeap::add(MinHeapNode* node){
    array.push_back(node);
}

int MinHeap::getSize(){
    return array.size();
}   

void MinHeap::generateCodes(MinHeapNode* node, std::vector<char> currCode){
    if(node->left){
        std::vector<char> tmp = currCode;
        tmp.push_back('0');
        generateCodes(node->left, tmp);
    }

    if(node->right){
        std::vector<char> tmp = currCode;
        tmp.push_back('1');
        generateCodes(node->right, tmp);
    }

    if(!node->left && !node->right){
        codes[node->data] = currCode;
    }
}
