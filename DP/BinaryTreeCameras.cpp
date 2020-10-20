#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <cmath>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define ll long long

class TreeNode{
public:
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x = 0): val(x), left(NULL), right(NULL) {}
};

int minCameraCover(TreeNode* root, int prevstate = 2)
{
	if(!root) return 0;

	if(prevstate == 0) return minCameraCover(root->left, 1) + minCameraCover(root->right, 1) + 1;
	else if(prevstate == 1){
		int a1 = minCameraCover(root->left, 2) + minCameraCover(root->right, 2);
		int a2 = minCameraCover(root->left, 1) + minCameraCover(root->right, 1) + 1;
		return min(a1, a2);
	}
	else{
		int a1 = INT_MAX, a2 = INT_MAX;
		if(root->left){
			a1 = minCameraCover(root->left, 0) + minCameraCover(root->right, 2);
		}
		if(root->right){
			a1 = min(a1, minCameraCover(root->left, 2) + minCameraCover(root->right, 0));
		}
		a2 = minCameraCover(root->left, 1) + minCameraCover(root->right, 1) + 1;
		return min(a1, a2);
	}

}

TreeNode* takeInput(){
	TreeNode *root = NULL;
	queue<TreeNode*> q;
	int d;
	cin >> d;
	if(d != -1){
		root = new TreeNode(d);
		q.push(root);
	}

	while(!q.empty()){
		TreeNode* curr = q.front();
		q.pop();
		cin >> d;
		if(d != -1){
			curr->left = new TreeNode(d);
			q.push(curr->left);
		}
		cin >> d;
		if(d != -1){
			curr->right = new TreeNode(d);
			q.push(curr->right);
		}
	}

	return root;

}

void AssignValues(TreeNode *root,int &counter)
{
	if(!root) return;
	root->val = counter++;
	AssignValues(root->left, counter);
	AssignValues(root->right, counter);
}

int main(){
	TreeNode* root = takeInput();
	int counter = 0;
	AssignValues(root, counter);
	vvi dp(counter, vi(3, -1));
	cout << minCameraCover(root, 2) << "\n";
	return 0;
}

