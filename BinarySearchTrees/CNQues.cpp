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


template <typename T>
class BinaryTreeNode{
public:
	T data;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode(T data){
		this->data = data;
		left = NULL, right = NULL;
	}

	~BinaryTreeNode(){
		delete left;
		delete right;
	}
};

//	Min Max Of Binary Tree
pair<int,int> minMax(BinaryTreeNode<int> *root){
	if(!root){
		return pair<int,int> (INT_MAX, INT_MIN);
	}
	pair<int,int> leftans = minMax(root->left);
	pair<int,int> rightans = minMax(root->right);

	pair<int,int> ans;
	ans.first = min(root->data, min(leftans.first, rightans.first));
	ans.second = max(root->data, max(leftans.second, rightans.second));

	return ans;
}

pair<bool,int> checkBalance(BinaryTreeNode<int>* root){

	if(!root){
		return pair<bool,int> (true, 0);
	}

	pair<bool,int> leftans = checkBalance(root->left);
	pair<bool,int> rightans = checkBalance(root->right);

	pair<bool,int> ans;
	ans.second = max(leftans.second, rightans.second) + 1;
	ans.first = (leftans.first&&rightans.first)&&(abs(leftans.second - rightans.second) <= 1);
	return ans;
}

//	Level Order Traversal
void PrintLevelOrderTraversal(BinaryTreeNode<int> *root){

	queue<BinaryTreeNode<int>* > q;
	q.push(root);
	q.push(NULL);
	while(q.size() > 1){
		BinaryTreeNode<int>* front = q.front();
		q.pop();
		if(!front){
			q.push(NULL);
			cout << "\n";
			continue;
		}
		cout << front->data << " ";
		if(front->left) q.push(front->left);
		if(front->right) q.push(front->right);
	}
}

//	Remove Leaf Nodes
BinaryTreeNode<int>* RemoveLeafNodes(BinaryTreeNode<int>* root){
	if(!root) return NULL;
	if(!root->left && !root->right){
		delete root;
		return NULL;
	}
	root->left = RemoveLeafNodes(root->left);
	root->right = RemoveLeafNodes(root->right);
	return root;
}


template <typename T>
class node{
public:
	T data;
	node<T> *next;
	node(T data){
		this->data = data;
		next = NULL;
	}
};


BinaryTreeNode<int>* takeInputLevelWise()
{
	int rootData;
	cout << "Enter root data\n";
	cin >> rootData;
	if(rootData == -1) return NULL;
	BinaryTreeNode<int>* root = new BinaryTreeNode<int>(rootData);
	queue<BinaryTreeNode<int>* > q;
	q.push(root);
	while(!q.empty()){
		BinaryTreeNode<int>* front = q.front();
		q.pop();
		cout << "Enter " << front->data << " left and right Child data\n";
		int leftChildData, rightChildData;
		cin >> leftChildData >> rightChildData;
		if(leftChildData != -1){
			BinaryTreeNode<int> *leftChild = new BinaryTreeNode<int>(leftChildData);
			front->left = leftChild;
			q.push(leftChild);
		}
		if(rightChildData != -1){
			BinaryTreeNode<int> *rightChild = new BinaryTreeNode<int>(rightChildData);
			front->right = rightChild;
			q.push(rightChild);
		}
	}
	return root;
}

void print(BinaryTreeNode<int>* root){
	if(!root) return;
	print(root->left);
	cout << root->data << " ";
	print(root->right);
}

vector<node<int>*> createLLForEachLevel(BinaryTreeNode<int> *root) {
    // Write your code here
    vector<node<int>* > ans;
	queue<BinaryTreeNode<int>* > q;
	q.push(root);
	node<int>* start = NULL;
	node<int>* last = NULL;
	q.push(NULL);
	while(q.size() > 1){
		BinaryTreeNode<int>* front = q.front();
		q.pop();
		if(!front){
			ans.push_back(start);
			q.push(NULL);
			start = NULL;
			last = NULL;
			continue;
		}
		if(!start && !last){
			start = new node<int>(front->data);
			last = start;
		}
		else{
			last->next = new node<int>(front->data);
			last = last->next;
		}
        if(front->left) q.push(front->left);
		if(front->right) q.push(front->right);
	}
	ans.push_back(start);
	return ans;
}

void helper(BinaryTreeNode<int>* root){
	queue<BinaryTreeNode<int>* > q;
	q.push(root);
	q.push(NULL);
	vector<int> v;
	while(q.size() > 1){
		BinaryTreeNode<int>* front = q.front();
		q.pop();
		if(!front){
			if(v.size() == 1) cout << v[0] << "\n";
			v.clear();
			q.push(NULL);
			continue;
		}
		v.push_back(front->data);
        if(front->left) q.push(front->left);
		if(front->right) q.push(front->right);
	}
	if(v.size() == 1) cout << v[0] << "\n";
}

//	Pair Sum BinaryTree
void dfs(BinaryTreeNode<int>* root,set<int>& ispresent){
	if(!root) return;
	ispresent.insert(root->data);
	dfs(root->left, ispresent);
	dfs(root->right, ispresent);
}

void nodesSumToS(BinaryTreeNode<int>* root,int S){
	set<int> ispresent;
	dfs(root, ispresent);
	while(!ispresent.empty())
	{
		int a = *(ispresent.begin());
		ispresent.erase(a);
		auto it2 = ispresent.find(S - a);
		if(it2 != ispresent.end()){
			cout << min(a, *it2) << " " << max(a, *it2) << "\n";
			ispresent.erase(it2);
		}
	}
}

pair<int, pair<bool, bool> > lcaBinaryTree(BinaryTreeNode<int>* root, int val1,int val2){

	if(!root) return pair<int, pair<bool,bool> > (-1, pair<bool,bool> (false, false));

	pair<int, pair<bool,bool> > leftans  = lcaBinaryTree(root->left, val1, val2);
	pair<int, pair<bool,bool> > rightans = lcaBinaryTree(root->right, val1, val2);
	if(leftans.second.first && leftans.second.second) return leftans;
	if(rightans.second.first && rightans.second.second) return rightans;
	pair<int, pair<bool,bool> > ans(-1, pair<bool,bool> (false, false));
	ans.first = root->data;
	if(val1 == root->data) ans.second.first = true;
	if(val2 == root->data) ans.second.second = true;

	if(leftans.second.first || rightans.second.first) ans.second.first = true;
	if(leftans.second.second || rightans.second.second) ans.second.second = true;

	return ans;
}

int lca(BinaryTreeNode<int>* root,int val1,int val2){
	if(!root) return -1;
	if(root->data == val2 || root->data == val1) return root->data;

	int leftans = lca(root->left, val1, val2);
	int rightans = lca(root->right, val1, val2);

	if(leftans != -1 && rightans != -1) return root->data;
	else{
		return max(leftans, rightans);
	}
}

//	1 2 3 4 5 -1 -1 -1 -1 6 -1 -1 -1
int main(){
	BinaryTreeNode<int>* root = takeInputLevelWise();
	vector<node<int>* > ans = createLLForEachLevel(root);
	for(int i=0;i<ans.size();i++){
		node<int>* start = ans[i];
		while(start){
			cout << start->data << " ";
			start = start->next;
		}
		cout << "\n";
	}
	print(root);
	delete root;

	return 0;
}

