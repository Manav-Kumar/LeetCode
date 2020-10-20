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

bool compare(const vi &a,const vi &b)
{
	if(a[1] != b[1]) return a[1] < b[1];
	return a[0] < b[0];
}



void buildTree(int *tree,int treeNode,int start,int end)
{
	if(start == end)
	{
		tree[treeNode] = start;
		return;
	}
	int mid = (start + end)/2;
	buildTree(tree,2*treeNode,start,mid);
	buildTree(tree,2*treeNode+1,mid+1,end);
	tree[treeNode] = min(tree[2*treeNode], tree[2*treeNode+1]);
}

int query(int start,int end,int *tree,int treeNode,int left,int right)
{
	//Completely Inside
	if(start >= left && end <= right) return tree[treeNode];
	//Completely Outside
	if(right < start || left > end) return INT_MAX;
	int mid = (start + end)/2;
	int a1 = query(start,mid,tree,2*treeNode,left,right);
	if(a1 != INT_MAX) return a1;
	int a2 = query(mid+1,end,tree,2*treeNode+1,left,right);
	return a2;
}

void update(int start,int end,int *tree,int treeNode,int idx)
{
	if(start == end)
	{
		tree[treeNode] = INT_MAX;
		return;
	}
	int mid = (start + end)/2;
	if(idx > mid) update(mid+1,end,tree,2*treeNode+1,idx);
	else update(start,mid,tree,2*treeNode,idx);
	tree[treeNode] = min(tree[2*treeNode],tree[2*treeNode+1]);
}

int maxEvents(vvi events)
{
	sort(events.begin(), events.end(), compare);
	int N = 10;
	int *tree = new int[4*N]();
	buildTree(tree,1,1,N);
	int count = 0, n = events.size();
	for(int i=0;i<n;i++)
	{
		int idx = query(1,N,tree,1,events[i][0], events[i][1]);
		if(idx != INT_MAX)
		{
			count++;
			update(1,N,tree,1,idx);
		}
	}
	for(int i=1;i<=3*N;i++)
	{
		cout << i << " " << tree[i] << "\n";
	}
	delete []tree;
	return count;
}

int main()
{
	int n;
	cin >> n;
	vvi events = vvi(n, vi(2));
	for(vi &a: events) cin >> a[0] >> a[1];
	cout << maxEvents2(events) << "\n";
	return 0;
}
