#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>
#define rep(i, a, b) for(int i = a;i<b;i++)

int maximumGap(vector<int> &nums){
	int n = nums.size();
	if(n <= 1) return 0;
	int ans = 0;
	for(int i=0;i<n;i++){

	}
}

class ListNode{
public:
	int val;
	ListNode* next;

};


class Solution{
public:

	ListNode* sortElement(ListNode* head, ListNode* node){
		ListNode* temp = head, prev = NULL;
		while(temp && temp->val < node->val){
			prev = temp, temp = temp->next;
		}
		if(prev == NULL){
			//	Insert at head
			node->next = head;
			return node;
		}
		prev->next = node, node->next = temp;
		return head;
	}

	ListNode* insertionSortList(ListNode* head){
		if(!head) return NULL;
		ListNode *prev = head, curr = prev->next;
		while(curr){
			ListNode* next = curr->next;
			
		}
	}
};

int main(){

	return 0;
}









