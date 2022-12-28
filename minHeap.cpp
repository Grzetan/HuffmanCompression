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
    int child = 2*i + 1;
    int res = (child < arr.size()) ? child : -1;
    return res;
}

int MinHeap::rightChild(int i){
    int child = 2*i + 2;
    int res = (child < arr.size()) ? child : -1;
    return res;
}

bool MinHeap::isLeaf(int i){
    return rightChild(i) > -1 && leftChild(i) > -1;
}

void MinHeap::traverseDown(int i){
    int left = leftChild(i);
    int right = rightChild(i);

    int smallest = i;

    if(left < arr.size() && arr[left] < arr[i]){
        smallest = left;
    }
    
    if(right < arr.size() && arr[right] < arr[smallest]){
        smallest = right;
    }

    if(smallest != i){
        std::swap(arr[i], arr[smallest]);
        traverseDown(smallest);
    }
}

void MinHeap::insert(HeapNode node){
    arr.push_back(node);

    int curr = arr.size() - 1;

    while(curr > 0 && arr[parentNode(curr)] > arr[curr]){
        std::swap(arr[parentNode(curr)], arr[curr]);
        curr = parentNode(curr);
    }
}

void MinHeap::pop(){
    arr[0] = arr.back();
    arr.pop_back();
    traverseDown(0);
}

bool MinHeap::empty(){
    return arr.size() == 0;
}

HeapNode MinHeap::top(){
    return arr[0];
}

void MinHeap::generateCodes(int root, std::vector<char> currCode){
    int left = leftChild(root);
    int right = rightChild(root);
    std::cout << "MS " << arr[root].c << " " << left << ", " << right << std::endl;
    codes[arr[root].c] = currCode;

    if(left > -1){
        std::vector<char> newChars = currCode;
        newChars.push_back('0');
        generateCodes(left, newChars);
    }

    if(right > -1){
        std::vector<char> newChars = currCode;
        newChars.push_back('1');
        generateCodes(right, newChars);
    }
}