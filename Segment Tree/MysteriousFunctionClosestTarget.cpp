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
		return ;
	}
	int mid = (start + end)/2;
	buildTree(arr,tree,start,mid,2*treeNode);
	buildTree(arr,tree,mid+1,end,2*treeNode+1);
	tree[treeNode] = tree[2*treeNode]&tree[2*treeNode+1];
}

int query(int *tree,int start,int end,int left,int right,int treeNode)
{
	//Completely Inside
	if(start >= left && end <= right) return tree[treeNode];
	//Completely Outside
	if(right < start || left > end) return -1;
	int mid = (start + end)/2;
	int a1 = query(tree,start,mid,left,right,2*treeNode);
	int a2 = query(tree,mid+1,end,left,right,2*treeNode+1);
	if(a1 == -1 || a2 == -1) return max(a1,a2);
	return a1&a2;
}

int minDiff(int *arr,int n,int &target)
{
	int *tree = new int[4*n]();
	buildTree(arr,tree,0,n-1,1);
	int ans = abs(-1000000000 - target), l = 0, r = 0;
	while(r < n)
	{
		int val = query(tree,0,n-1,l,r,1);
		ans = min(ans, abs(val - target));
		if(ans == 0) return 0;
		if(val >= target) r++;
		else
		{
			if(l!=r)l++;
			else
			{
				l++,r++;
			}
		}
	}
	return ans;
}

//Sliding Window
int minDiff2(int *arr,int n,int &target)
{
	vector<int> v;
	v.push_back(arr[0]);
	for(int i=1;i<n;i++) if(arr[i] != arr[i-1]) v.push_back(arr[i]);
	long long t, ans = INT_MAX;

	for(int i=0;i<v.size();i++)
	{
		t = v[i];
		ans = min(ans, abs(t - target));
		for(int j=i+1;j<v.size();j++)
		{
			t &= v[j];
			ans = min(ans, abs(t - target));
			if(t < target || t == 0) break;
		}
	}
	return ans;
}


int main()
{
	int n, target;
	cin >> n;
	int *arr = new int[n];
	for(int i=0;i<n;i++) cin >> arr[i];
	cin >> target;
	cout << minDiff2(arr,n,target) << "\n";
	return 0;
}