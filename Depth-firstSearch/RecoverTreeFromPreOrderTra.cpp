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
#include <climits>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vi >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>


class TreeNode{
public:
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int v = 0): val(v), left(NULL), right(NULL) {}
	~TreeNode(){
		delete left;
		delete right;
	}
};


TreeNode* recoverFromPreorder(string s,int st,int en, int d = 0){

	if(st > en) return NULL;
	if(s[0] == '-') return recoverFromPreorder(s, st + 1, en, d);
	//	For child search nodes having depth d + 1
	int v = 0, i = st;
	while(i <= en && s[i] != '-'){
		v = v*10 + int(s[i++] - '0');
	}
	TreeNode *root = new TreeNode(v);

	int leftIdx = -1, rightIdx = -1;
	while(i <= en){
		int ct = 0;
		while(s[i] == '-') i++, ct++;
		if(ct == d + 1){
			if(leftIdx == -1) leftIdx = i;
			else if(rightIdx == -1) rightIdx = i;
			else break;
		}
		while(i <= en && s[i] != '-') i++;
	}

	if(leftIdx != -1){
		root->left = recoverFromPreorder(s, leftIdx, rightIdx == -1?en:rightIdx - 1,d + 1);
	}

	if(rightIdx != -1){
		root->right = recoverFromPreorder(s, rightIdx, en, d + 1);
	}

	return root;
}

void preOrder(TreeNode *root){
	if(!root) return;
	cout << root->val << " ";
	preOrder(root->left);
	preOrder(root->right);
}


int main(){
	string s;
	cin >> s;
	TreeNode *root = recoverFromPreorder(s, 0, s.size() - 1);
	preOrder(root);
	delete root;
	return 0;
}


