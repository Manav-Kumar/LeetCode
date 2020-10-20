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

//	To make this class generic i.e which can hold data for any data type we need to use template
template <typename T>
class BinaryTreeNode{
public:
	T data;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode(T data){
		this->data = data;
		left = NULL;
		right = NULL;
	}

	~BinaryTreeNode(){
		delete left;
		delete right;
	}
};

//	Destructor will be called when delete is called for dynamically allocated memory of above data 
//	type variable or when simple local variable goes out of scope


void printTree(BinaryTreeNode<int> *root){
	//	Base Case
	if(root == NULL) return;

	cout << root->data << ":";
	if(root->left != NULL) cout << "L" << root->left->data;
	if(root->right != NULL) cout << "R" << root->right->data;
	cout << endl;
	printTree(root->left);
	printTree(root->right);
}

void printTreeLevelWise(BinaryTreeNode<int>* root){
	if(root==NULL) return;
	queue<BinaryTreeNode<int>* > pendingNodes;
	pendingNodes.push(root);
	while(!pendingNodes.empty()){
		BinaryTreeNode<int>* front = pendingNodes.front();
		pendingNodes.pop();
		cout << front->data << ":";
		if(front->left != NULL){
			cout << "L" << front->left->data;
			pendingNodes.push(front->left);
		}
		if(front->right != NULL){
			cout << "R" << front->left->data;
			pendingNodes.push(front->right);
		}
		cout << "\n";
	}
}

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

BinaryTreeNode<int>* takeInput()
{
	int rootData;
	cin >> rootData;
	if(rootData == -1){
		return NULL;
	}
	BinaryTreeNode<int>* root = new BinaryTreeNode<int>(rootData);
	BinaryTreeNode<int>* leftChild = takeInput();
	BinaryTreeNode<int>* rightChild = takeInput();
	root->left = leftChild;
	root->right = rightChild;
	return root;
}

int numNodes(BinaryTreeNode<int>* root){
	if(root == NULL) return 0;
	return 1 + numNodes(root->left) + numNodes(root->right);
}

void mirrorBinaryTree(BinaryTreeNode<int>* root){
	if(!root) return;
	mirrorBinaryTree(root->left);
	mirrorBinaryTree(root->right);
	BinaryTreeNode<int>* temp = root->left;
	root->left = root->right;
	root->right = temp;
}

//	Constructing Unique Tree from PreOrder and InOrder
BinaryTreeNode<int>* ConstructTree(int *PreOrder,int *InOrder,int preSt,int preEn,int inSt,int inEn){
	//	Base Case
	if(inSt > inEn) return NULL;

	int rootData = PreOrder[preSt];
	BinaryTreeNode<int>* root = new BinaryTreeNode<int>(rootData);
	int rootIdxInorder;
	for(int i=inSt;i<=inEn;i++) if(InOrder[i] == rootData) {rootIdxInorder = i; break;}

	//preLeftEn - (preSt+1) = (rootIdxInorder-1) - inSt;
	int preLeftEn = rootIdxInorder - inSt + preSt;
	root->left = ConstructTree(PreOrder, InOrder, preSt+1, preLeftEn,inSt,rootIdxInorder - 1);
	root->right = ConstructTree(PreOrder, InOrder, preLeftEn+1 ,preEn, rootIdxInorder + 1,inEn);
	return root;
}

//	Constructing Unique Tree from PostOrder and InOrder
BinaryTreeNode<int>* ConstructTreePost(int *PostOrder,int *InOrder,int posSt,int posEn,int inSt,int inEn){
	//	Base Case
	if(posSt > posEn) return NULL;

	int rootData = PostOrder[posEn];
	BinaryTreeNode<int>* root = new BinaryTreeNode<int>(rootData);
	int rootIdxInorder;
	for(int i=inSt;i<=inEn;i++) if(InOrder[i] == rootData) {rootIdxInorder = i; break;}

	// posLeftEn - posSt = rootIdxInorder-1 - inSt;
	int posLeftEn = (rootIdxInorder - 1) - inSt + posSt;
	root->left = ConstructTreePost(PostOrder,InOrder,posSt,posLeftEn,inSt, rootIdxInorder-1);
	root->right = ConstructTreePost(PostOrder,InOrder, posLeftEn + 1,posEn-1, rootIdxInorder+1,inEn);
	return root;
}

//	Diameter of Binary Tree
int DiameterBinaryTree(BinaryTreeNode<int>* root){
	if(!root){
		return pair<int,int> (0, 0);
	}
	pair<int,int> lefData = DiameterBinaryTree(root->left);
	pair<int,int> rightData = DiameterBinaryTree(root->right);
	pair<int,int> ans;
	ans.first = max(lefData.first, rightData.first) + 1;
	ans.second = max(max(lefData.second, rightData.second), lefData.first + rightData.first);
	return ans;
}


int main(){
	// BinaryTreeNode<int> *root = new BinaryTreeNode<int>(1);
	// BinaryTreeNode<int> *node1 = new BinaryTreeNode<int>(2);
	// BinaryTreeNode<int> *node2 = new BinaryTreeNode<int>(3);
	// root->left = node1;
	// root->right = node2;
	BinaryTreeNode<int> *root = takeInputLevelWise();
	printTree(root);
	cout << "Num :" << numNodes(root) << "\n";
	delete root;
	return 0;
}

