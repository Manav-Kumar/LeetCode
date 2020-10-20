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
#include <deque>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vl vector<long>
#define vll vector<long long>
#define vc vector<char>
#define vs vector<string>
#define vvc vector<vc>
#define vvi vector<vector<int> >
#define vvvi vector<vvi>
#define vvl vector<vl>
#define vvll vector<vll>
#define vvb vector<vector<bool> >
#define vvvb vector<vvb>

class trieNode{
public:
	trieNode* left;
	trieNode* right;
	int ct;
	trieNode(): left(NULL), right(NULL), ct(0) {}
};


void insert(trieNode *head,int value){

	trieNode *curr = head;
	for(int j=31;j>=0;j--){
		int b = (value>>j)&1;
		curr->ct += 1;
		if(b == 0){
			if(!curr->left) curr->left = new trieNode();
			curr = curr->left;
		}
		else{
			if(!curr->right) curr->right = new trieNode();
			curr = curr->right;
		}
	}
	curr->count += 1;
}

//	Sub Array XOR Less Than K
int SubArrayLessThanK(int *arr,int n,int k){

	trieNode *head = new trieNode();
	int prev = 0, count = 0;
	for(int i=0;i<n;i++){
		prev ^= arr[i];
		if(prev < k) count += 1;
		int value = prev;
		trieNode *curr = head;
		for(int j=31;j>=0;j--){

			int b = (value>>j)&1, bk = (k>>j)&1;
			if(bk == 0){
				if(b == 0) curr = curr->left;
				else curr = curr->right;
			}
			else{
				if(b == 0){
					if(curr->left) count += curr->left->ct; 
					curr = curr->right;
				}
				else{
					if(curr->right) count += curr->right->ct;
					curr = curr->left;
				}
			}
			if(curr == NULL) break;
		}
		insert(head, prev);
	}
	return count;
}


int main()
{
	int n,k;
	cin >> n >> k;
	int *arr = new int[n];
	for(int i=0;i<n;i++) cin >> arr[i];
	cout << SubArrayLessThanK(arr, n, k) << "\n";
	delete []arr;
	return 0;
}

