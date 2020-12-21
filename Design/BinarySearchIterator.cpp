#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <random>
using namespace std;

#define vi vector<int>

int main(){

	return 0;
}

class CustomStack {
    vector<int> arr;
    vector<int> updates;
    int idx;
public:
    CustomStack(int maxSize): arr(maxSize, 0), updates(maxSize, 0), idx(0) {
        
    }
    
    void push(int x) {
        if(idx < arr.size()){
            arr[idx++] = x;
        }
    }
    
    int pop() {
        if(idx == 0) return -1;
        int ret = arr[--idx];
        return ret;
    }
    
    void increment(int k, int val) {
        if(idx == 0) return;
        for(int i = 0;i < min(idx, k);i++) arr[i] += val;
    }
};