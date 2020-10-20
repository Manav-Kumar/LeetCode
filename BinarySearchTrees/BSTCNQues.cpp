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

bool CheckBST(BinaryTreeNode<int>* root,int st = INT_MIN,int en = INT_MAX){
	if(!root) return true;

	if(root->data < st || root->data > en) return false;

	return CheckBST(root->left, st, root->data) && CheckBST(root->right, root->data, en);
}

int height(BinaryTreeNode<int>* root){
	if(!root) return 0;
	return 1 + max(height(root->left), height(root->right));
}
//	O(n*H)
int largestBSTSubtree(BinaryTreeNode<int>* root){

	if(!root) return 0;

	if(CheckBST(root)) return height(root);

	return max(largestBSTSubtree(root->left), largestBSTSubtree(root->right));
}

class isBST{
public:
	int Min, Max, height;
	bool Check;
	isBST(): Min(INT_MAX), Max(INT_MIN), Check(true), height(0) {}
};



isBST Helper(BinaryTreeNode<int>* root){

	if(!root) return isBST();

	isBST leftans = Helper(root->left);
	isBST rightans = Helper(root->right);
	isBST ans;
	if(!leftans.Check || !rightans.Check || root->data < leftans.Max || root->data >= rightans.Min)
		ans.Check = false;
	ans.Min = min(root->data, leftans.Min);
	ans.Max = max(root->data, rightans.Max);
	ans.height = max(leftans.height, rightans.height);
	if(ans.Check) ans.height += 1;
	return ans;
}


BinaryTreeNode<int>* bstToGST(BinaryTreeNode<int>* root,int& value){

	if(!root) return NULL;
	root->right = bstToGST(root->right, value);
	root->data += value;
	value = root->data;
	root->left =  bstToGST(root->left, value);
	return root;
}



isBST maxSumBST(BinaryTreeNode<int>* root,int &possibleAns){

	if(!root) return isBST();

	isBST leftans = maxSumBST(root->left, possibleAns);
	isBST rightans = maxSumBST(root->right, possibleAns);
	isBST ans;
	if(!leftans.Check || !rightans.Check || root->data < leftans.Max || root->data >= rightans.Min){
		ans.Check = false;
	}

	if(ans.Check) ans.height = root->data + leftans.height + rightans.height;
	else ans.height = max(leftans.height, rightans.height);
	possibleAns = max(possibleAns, ans.height);

	ans.Min = min(root->data, min(leftans.Min, rightans.Min));
	ans.Max = max(root->data, max(leftans.Max, rightans.Max));
	return ans;
}

BinaryTreeNode<int>* rotateLeft(BinaryTreeNode<int>* root){
	BinaryTreeNode<int>* temp = root->right;
	root->right = temp->left;
	temp->left = root;
	return temp;
}

BinaryTreeNode<int>* rotateRight(BinaryTreeNode<int>* root){
	BinaryTreeNode<int>* temp = root->left;
	root->left = temp->right;
	temp->right = root;
	return temp;
}

// class triplet{
// public:
// 	int lh, rh, th;
// 	triplet(int a=0,int b=0,int c=0): lh(a), rh(b), th(c) {}
// };

// pair<triplet,BinaryTreeNode<int>* > balanceBST(BinaryTreeNode<int>* root){

// 	if(!root) return pair<triplet, BinaryTreeNode<int>* > (triplet(), NULL);

// 	pair<triplet, BinaryTreeNode<int>* > a1 = balanceBST(root->left);
// 	pair<triplet, BinaryTreeNode<int>* > a2 = balanceBST(root->right);	
// 	triplet leftans = a1.first;
// 	triplet rightans = a2.first;

// 	if(abs(leftans.th - rightans.th) <= 1){
// 		return pair<triplet, BinaryTreeNode<int>* > (triplet(leftans.th, rightans.th, max(leftans.th, rightans.th) + 1), root);
// 	}

// 	if(leftans.th > rightans.th){
// 		if(leftans.lh > leftans.rh){
// 			root->left = rotateRight(root->left);
// 		}
// 		root = rotateRight(root);
// 		leftans.th--;
// 		rightans.th++;
// 	}
// 	else{
// 		if(rightans.rh > rightans.lh){
// 			root->right = rotateLeft(root->right);
// 		}
// 		root = rotateLeft(root);
// 		rightans.th--;
// 		leftans.th++;
// 	}
// 	return pair<triplet, BinaryTreeNode<int>* > (triplet(leftans.th, rightans.th, max(leftans.th, rightans.th) + 1), root);
// }


// BinaryTreeNode<int>* balanceBST2(BinaryTreeNode<int>* root){

// 	if(!root) return NULL;

// 	root->left = balanceBST2(root->left);
// 	root->right = balanceBST2(root->right);
// 	int lht = height(root->left), rht = height(root->right);
// 	if(abs(lht - rht) <= 1) return root;

// 	if(lht > rht){
// 		int llht = height(root->left->left), lrht = height(root->left->right);
// 		if(lrht > llht){
// 			root->left = rotateLeft(root->left);
// 		}
// 		root = rotateRight(root);
// 	}
// 	else{
// 		int rlht = height(root->right->left), rrht = height(root->right->right);
// 		if(rlht > rrht){
// 			root->right = rotateRight(root->right);
// 		}
// 		root = rotateLeft(root);
// 	}
// 	return root;
// }

//	ABOVE WRITTEN APPROACH IS WRONG AS IT IS VALID WHEN WE ARE TRYING TO INSERT NEW NODES ONE BY 
//		ONE IN THE ALREADY FORMED BALANCED BST SO THAT MAXIMUM DIFF COULDN'T BE GREATER THAN 2.

void inorder(BinaryTreeNode<int>* root,vector<int> &arr){
	if(!root) return;
	inorder(root->left, arr);
	arr.push_back(root->data);
	inorder(root->right, arr);
}

BinaryTreeNode<int>* balanceBSTHelper(vector<int> &arr,int st,int en){
	if(st > en) return NULL;
	if(st == en) return new BinaryTreeNode<int>(arr[st]);

	int mid = (st + en)/2;
	BinaryTreeNode<int>* root = new BinaryTreeNode<int>(arr[mid]);
	root->left = balanceBSTHelper(arr, st,mid-1);
	root->right = balanceBSTHelper(arr, mid + 1, en);
	return root;
}

BinaryTreeNode<int>* balanceBST(BinaryTreeNode<int>* root){
	vector<int> arr;
	inorder(root, arr);
	//Here we are going to get the sorted array
	root = balanceBSTHelper( arr, 0, arr.size() - 1);
	return root;
}


void rootToLeafPathsSumToK(BinaryTreeNode<int>* root,int k, vector<int> arr){

	//	Edge Case
	if(!root || k < 0) return;
	//	Base Case
	if(!root->left && !root->right){
		k -= root->data;
		arr.push_back(root->data);
		if(k != 0) return;
		for(int &a: arr) cout << a << " ";
		cout << "\n";
		return;
	}

	arr.push_back(root->data);
	rootToLeafPathsSumToK(root->left, k - root->data, arr);
	rootToLeafPathsSumToK(root->right, k - root->data, arr);
}

void helper(BinaryTreeNode<int>* root, int k,int val){

	if(!root || k < 0) return;
	if(k == 0){
		if(root->data) cout << root->data << " ";
		return;
	}
	helper(root->left, k - 1, val);
	helper(root->right, k - 1, val);
}

int nodesAtDistanceK(BinaryTreeNode<int>* root, int node, int k){

	if(!root) return -1;

	if(root->data == node){
		helper(root, k, node);
		return 1;
	}
	int leftans = nodesAtDistanceK(root->left, node, k);
	int rightans = nodesAtDistanceK(root->right, node, k);

	if(leftans != -1){
		if(k > leftans) helper(root->right, k - leftans - 1, node);
		else if(k == leftans) cout << root->data << "ok ";
	}

	if(rightans != -1){
		if(k > rightans) helper(root->left, k - rightans - 1, node);
		else if(k == rightans) cout << root->data << "ok ";
	}

	return max(leftans, rightans) == -1?-1: max(leftans, rightans) + 1;
}

void printTree(BinaryTreeNode<int> *root){

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

void Search(BinaryTreeNode<int>* root, int val, int fix){
	if(!root) return;
	if(root->data == val){
		cout << fix << " " << val << "\n";
		return;
	}
	if(val > root->data) Search(root->right, val, fix);
	else Search(root->left, val, fix);
}

void printNodesSumToS(BinaryTreeNode<int>* root,int s, BinaryTreeNode<int>* curr){

	if(!curr) return;

	int temp = s - curr->data;
	if(curr->data >= temp) {}
	else Search(root, temp, curr->data);

	printNodesSumToS(root, s, curr->left);
	printNodesSumToS(root, s, curr->right);
}

void printNodesSumToS2(BinaryTreeNode<int>* root, int s){

	
}

int main(){
	BinaryTreeNode<int>* root = takeInputLevelWise();
	int node, k;
	cout << "\nEnter node and k\n";
	cin >> node >> k; 
	cout << nodesAtDistanceK(root, node, k) << "\n";
	return 0;
}


