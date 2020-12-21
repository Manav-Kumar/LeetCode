#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <random>
using namespace std;

//	Design SkipList which takes O(log(n)) time to add, erase and search, 
//		Comparing with treap and red-black tree which has same function and performance,
//		here code length comparatively short and the idea behind skiplist are just simple link list

bool flipCoin(){

}

class Node{
public:
	int val;
	vector<Node*> next;
	Node(int v = 0): val(v), next(4, NULL){
	}
};

class SkipList{
public:
	Node* head;

	SkipList(){

	}

	bool search(int target){
		Node* curr = head;
		Node* prev = NULL;
		int level = 3;
		while(curr != NULL){
			if(curr->val == target) return true;
			else if(curr->val > target)  break;
			prev = curr, curr = curr->next[level];
		}
		curr = prev, level--, prev = NULL;

		while(curr != NULL){
			if(curr->val == target) return true;
			else if(curr->val > target) break;
			prev = curr, curr = curr->next[level];
		}
		curr = prev, level--, prev = NULL;

		while(curr != NULL){
			if(curr->val == target) return true;
			else if(curr->val > target) break;
			prev = curr, curr = curr->next[level];
		}
		curr = prev, level--, prev = NULL;

		while(curr != NULL){
			if(curr->val == target) return true;
			else if(curr->val > target) break;
			prev = curr, curr = curr->next[level];
		}

		if(curr && curr->val == target) return true;
		return false;

	}

	void add(int num){
		if(num < head->val){
			
			return;
		}
		Node* curr = head;
		Node* prev = NULL;
		vector<Node*> StartFrom;
		int level = 3;
		while(level--){
			while(curr != NULL){
				if(curr->val > num) break;
				prev = curr;
			}
			StartFrom.push(prev);
			curr = prev, prev = NULL;
		}

	}

	bool erase(int num){

	}

};

int main(){

	return 0;
}