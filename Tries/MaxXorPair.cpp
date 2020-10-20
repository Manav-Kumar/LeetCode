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
	trieNode(): left(NULL), right(NULL) {}
};

void insert(int value,trieNode *head){

	trieNode* curr = head;
	for(int i=31;i>=0;i--){
		int b = (value>>i)&1;

		if(b == 0){
			if(!curr->left) curr->left = new trieNode();
			curr = curr->left;
		}
		else{
			if(!curr->right) curr->right = new trieNode();
			curr = curr->right;
		}
	}
}

int findMaxXorPair(trieNode *head,int *arr,int n){

	int max_xor = INT_MIN;

	for(int i=0;i<n;i++){
		int curr_xor = 0, value = arr[i];;
		trieNode *curr = head;
		for(int j=31;j>=0;j--){
			int b = (value>>j)&1;
			if(b == 0){
				if(curr->right){
					curr = curr->right;
					curr_xor += (1<<j);
				}
				else curr = curr->left;
			}
			else{ 
				if(curr->left){
					curr = curr->left;
					curr_xor += (1<<j);
				}
				else curr = curr->right;
			}
		}
		max_xor = max(max_xor, curr_xor);
		insert(arr[i], head);
	}
	return max_xor;
}


//	MaxXor Sub Array
int MaxXorSubArray(int *arr,int n)
{
	trieNode *head = new trieNode();
	int max_xor = arr[0], prev = arr[0];
	insert(arr[0], head);
	for(int i=1;i<n;i++)
	{
		prev ^= arr[i];
		int curr_xor = 0, value = prev;
		trieNode* curr = head;
		for(int j=31;j>=0;j--){
			int b = (value>>j)&1;
			if(b == 0){
				if(curr->right){
					curr_xor += (1<<j);
					curr = curr->right;
				}
				else curr = curr->left;
			}
			else{
				if(curr->left){
					curr_xor += (1<<j);
					curr = curr->left;
				}
				else curr = curr->right;
			}
		}
		max_xor = max(max_xor, max(curr_xor, prev));
		insert(prev, head);
	}
	return max_xor;
}



int main()
{
	int arr[6] = {8, 1, 2, 15, 10, 5};
	trieNode *head = new trieNode();
	for(int i=0;i<6;i++) insert(arr[i], head);
	cout << findMaxXorPair(head, arr, 6) << "\n";
	return 0;
}

