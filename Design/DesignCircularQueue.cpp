#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <random>
using namespace std;

#define vi vector<int>


class MyCircularQueue{
	vi array;
	int headIdx, tailIdx, cap;
public:
	MyCircularQueue(int k): array(k, 0), cap(k) {
		headIdx = -1, tailIdx = -1;
	}

	bool enQueue(int value){
		if(headIdx == tailIdx && headIdx != -1) return false;
		if(headIdx == -1) headIdx = 0, tailIdx = 0;
		array[tailIdx] = value;
		tailIdx = (tailIdx + 1)%cap;
		return true;
	}

	bool deQueue(){
		if(headIdx == -1) return false;
		headIdx = (headIdx + 1)%cap;
		if(headIdx == tailIdx) headIdx = -1, tailIdx = -1;
		return true;
	}

	bool isEmpty(){
		return headIdx == -1;
	}

	bool isFull(){
		return headIdx != -1 && headIdx == tailIdx;
	}

	int Front(){
		if(isEmpty()) return -1;
		return array[headIdx];
	}
	int Rear(){
		if(isEmpty()) return -1;
		return tailIdx == 0?array[cap - 1]:array[tailIdx - 1];
	}
};



class MyCircularQueue{
    int cap;
	vector<int> store;
public:
	MyCircularQueue(int k):cap(k) {
        
	}

	bool enQueue(int value){
		if(store.size() == cap) return false;
		store.push_back(value);
		return true; 
		
	}

	bool deQueue(){
		if(store.empty()) return false;
		store.erase(store.begin(), store.begin() + 1);
		return true;
		
	}

	bool isEmpty(){
		return store.size() == 0;
	}

	bool isFull(){
		return store.size() == cap;
	}

	int Front(){
		if(isEmpty()) return -1;
		return store[0];
	}
	int Rear(){
		if(isEmpty()) return -1;
		return store[store.size() - 1];
	}
};

int main(){

	return 0;
}

