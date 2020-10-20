#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <cmath>
#include <math.h>
#include <unordered_set>
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
#define vvc vector<vc>
#define vvi vector<vector<int> >
#define vvl vector<vl>
#define vvll vector<vll>
#define vvb vector<vector<bool> >

void buildTree(int *arr,int *tree,int start,int end,int treeNode)
{
	if(start == end)
	{
		tree[treeNode] = arr[start];
		return;
	}
	int mid = (start + end)/2;
	buildTree(arr,tree,start,mid,2*treeNode);
	buildTree(arr,tree,mid+1,end,2*treeNode+1);
	tree[treeNode] = tree[2*treeNode] + tree[2*treeNode+1];
}

void UpdateTree(int *arr,int *tree,int start,int end,int treeNode,int idx,int value)
{
	if(start == end)
	{
		arr[idx] = value;
		tree[treeNode] = value;
		return;
	}
	int mid = (start + end)/2;
	if(idx > mid) UpdateTree(arr,tree,mid+1,end,2*treeNode+1,idx,value);
	else UpdateTree(arr,tree,start,mid,2*treeNode,idx,value);
	tree[treeNode] = tree[2*treeNode] + tree[2*treeNode+1];
}

int query(int *tree,int start,int end,int treeNode,int left,int right)
{
	//Completely Inside
	if(start >= left && end <= right) return tree[treeNode];
	//Completely Outside
	if(right < start || left > end) return 0;
	int mid = (start + end)/2;
	int a1 = query(tree,start,mid,2*treeNode,left,right);
	int a2 = query(tree,mid+1,end,2*treeNode+1,left,right);
	return a1+a2;
}


int main()
{
	int arr[] = {1,2,3,4,5,6};
	int *tree = new int[4*6]();
	buildTree(arr,tree,0,5,1);
	for(int i=0;i<4*6;i++) cout << tree[i] << "\n";
	return 0;
}