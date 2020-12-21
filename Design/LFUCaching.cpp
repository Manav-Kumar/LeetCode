#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <unordered_map>
#include <set>
#include <cmath>
#include <math.h>
#include <unordered_set>
#include <list>
#include <climits>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vll vector<ll>
#define vi vector<int>
#define vvi vector<vi >
#define vvvi vector<vvi>
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>

//	Least Frequently Used
// class node{
// public:
// 	int key, val, timestap;
// 	node* next;
// 	node* prev;
// 	node(int k,int v,int t): key(k), val(v), timestap(t), next(NULL), prev(NULL) {}
// };


// class LFUCache{
// 	int capacity, timestap, count;
// 	map<int,int> freq;
// 	map<int,node*> mp;
// public:
// 	LFUCache(int capacity): capacity(capacity){
// 		timestap = 0, count = 0;
// 	}

// 	int get(int key){
// 		if(mp.count(key) == 0) return -1;
// 		freq[key] += 1, (mp[key])->timestap = timestap++;
// 		return (mp[key])->val;
// 	}

// 	void put(int key, int value){
// 		if(mp.count(key) == 0){
// 			node* t = new node(key, value, timestap++);

// 			if(count == capacity){
// 				//	Remove The Least Frequently Used key and with least timestamp
// 				int k = -1, t = INT_MAX, f = INT_MAX;
// 				for(auto it = freq.begin();it != freq.end();it++){
// 					if(it->second < f){
// 						f = it->second, k = it->first, t = mp[k]->timestap;
// 					}
// 					else if(it->second == f && (mp[it->first])->timestap < t){
// 						k = it->first, t = mp[k]->timestap;
// 					}
// 				}
// 				if(k != -1) freq.erase(k), mp.erase(k), count--;
// 			}

// 			if(count < capacity) mp[key] = t, count++, freq[key] += 1;

// 		}
// 		else freq[key] += 1, (mp[key])->val = value, (mp[key])->timestap = timestap++;
// 	}
// };




struct Entry{ int val, freq; list<int>::iterator itr; };

class LFUCache {
    unordered_map<int,Entry> entries;
    unordered_map<int,list<int>> lists;
    int caps, minm;
public:
    LFUCache(int capacity) {
        caps = capacity;
        minm = 0;
    }
    
    int get(int key) {
        if(!entries.count(key))    return -1;
        Entry entry = entries[key];
        //erase item in old frequency list
        lists[entry.freq].erase(entry.itr);  
        //update minm if no items is present in minm frequency list
        if(entry.freq==minm and lists[minm].empty()) minm++;
        //push item in new frequency list and save iterator
        lists[++entry.freq].push_back(key);
        entry.itr = --lists[entry.freq].end();
        entries[key] = entry;
        return entry.val;
    }
    
    void put(int key, int value) {
        if(caps<=0) return;
        if(entries.count(key)) {
			//key is present
            entries[key].val = value;
            get(key);   //update frequency
            return;
        }
        if(caps==entries.size()) { 
			//if size is caps remove the element with least frequency
            int rkey = *lists[minm].begin();
            lists[minm].erase(lists[minm].begin());
            entries.erase(rkey);
        }
        minm = 1; //push item in minm = 1 frequency list
        lists[minm].push_back(key);
        entries[key] = {value,minm,--lists[minm].end()};
    }
};



int main(){
	return 0;
}



