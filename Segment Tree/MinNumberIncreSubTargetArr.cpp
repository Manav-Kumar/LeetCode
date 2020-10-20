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


pair<int,int> query(int start,int end,pair<int,int> *tree,int *lazy,int treeNode,int left,int right)
{
	if(lazy[treeNode] != 0)
	{
		tree[treeNode].first -= lazy[treeNode];
		if(start != end)
		{
			lazy[2*treeNode] += lazy[treeNode];
			lazy[2*treeNode+1] += lazy[treeNode];
		}
		lazy[treeNode] = 0;
	}
	//Completely Inside
	if(start >= left && end <= right) return tree[treeNode];
	//Completely Outside
	if(right < start || end < left) return pair<int,int>(INT_MAX,-1);
	int mid = (start + end)/2;
	pair<int,int> a1 = query(start,mid,tree,lazy,2*treeNode,left,right);
	pair<int,int> a2 = query(mid+1,end,tree,lazy,2*treeNode+1,left,right);
	return a1.first <= a2.first? a1:a2;
}

void update(int start,int end,pair<int,int> *tree,int *lazy,int treeNode,int left,int right,int minValue)
{
	if(lazy[treeNode] != 0)
	{
		tree[treeNode].first -= lazy[treeNode];
		if(start != end)
		{
			lazy[2*treeNode] += lazy[treeNode];
			lazy[2*treeNode+1] += lazy[treeNode];
		}
		lazy[treeNode] = 0;
	}
	//Completely Inside
	if(start >= left && end <= right)
	{
		tree[treeNode].first -= minValue;
		if(start != end)
		{
			lazy[2*treeNode] += minValue;
			lazy[2*treeNode+1] += minValue;
		}
		return;
	}
	//Completely Outside
	if(right < start || end < left) return ;
	int mid = (start + end)/2;
	update(start,mid,tree,lazy,2*treeNode,left,right,minValue);
	update(mid+1,end,tree,lazy,2*treeNode+1,left,right,minValue);
	pair<int,int> a1 = tree[2*treeNode];
	pair<int,int> a2 = tree[2*treeNode+1];
	pair<int,int> ans;
	if(a1.first <= a2.first) tree[treeNode] = a1;
	else tree[treeNode] = a2;
}

int minNumberOp(pair<int,int> *tree,int *lazy,int st,int en,int n)
{

	if(st > en) return 0;
	pair<int,int> minValue = query(0,n-1,tree,lazy,1,st,en);
	update(0,n-1,tree,lazy,1,st,en,minValue.first);

	int ans = minNumberOp(tree, lazy, st,minValue.second-1,n) +
			 minNumberOp(tree, lazy, minValue.second+1,en,n) + minValue.first;
	return ans;
}


void buildTree(int *target,int start,int end,pair<int,int> *tree,int treeNode)
{
	if(start == end)
	{
		tree[treeNode] = pair<int,int>(target[start], start);
		return;
	}
	int mid = (start + end)/2;
	buildTree(target, start, mid, tree, 2*treeNode);
	buildTree(target, mid+1, end, tree, 2*treeNode+1);
	if(tree[2*treeNode].first <= tree[2*treeNode+1].first) tree[treeNode] = tree[2*treeNode];
	else tree[treeNode] = tree[2*treeNode+1];
}

int main()
{
	int n;
	cin >> n;
	int *target = new int[n];
	for(int i=0;i<n;i++) cin >> target[i];
	pair<int,int> *tree = new pair<int,int>[4*n];
	int *lazy = new int[4*n]();
	buildTree(target, 0,n-1,tree,1);
	cout << minNumberOp(tree, lazy,0,n-1,n) << "\n";
	return 0;
}

