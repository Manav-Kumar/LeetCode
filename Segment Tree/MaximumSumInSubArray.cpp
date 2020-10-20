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

//Return the maximum sum of subarray
class node
{
public:
	int maxSum, maxPre, maxSuff, total;
	node(int val = 0): maxSum(val), maxPre(val), maxSuff(val), total(val) {}
};

void buildTree(int *arr,node *tree,int start,int end,int treeNode)
{
	if(start == end)
	{
		node ans(arr[start]);
		tree[treeNode] = ans;
		return;
	}
	int mid = (start + end)/2;
	buildTree(arr,tree,start,mid,2*treeNode);
	buildTree(arr,tree,mid+1,end,2*treeNode+1);

	node ans, left = tree[2*treeNode], right = tree[2*treeNode+1];
	ans.maxSum = max(left.maxSuff + right.maxPre , max(left.maxSum, right.maxSum));
	ans.maxPre = max(left.maxPre, left.total + right.maxPre);
	ans.maxSuff = max(left.maxSuff + right.total,right.maxSuff);
	ans.total = left.total + right.total;
	tree[treeNode] = ans;
}

node query(node *tree,int start,int end,int treeNode,int left,int right)
{
	//Completely Inside
	if(start >= left && end <= right) return tree[treeNode];
	//Completely Outside
	if(right < start || left > end) return node(INT_MIN);
	int mid = (start + end)/2;
	node a1 = query(tree, start, mid,2*treeNode,left,right);
	node a2 = query(tree, mid+1, end,2*treeNode+1, left, right);
	node ans;
	if(a1.total == INT_MIN || a2.total == INT_MIN) return a1.total == INT_MIN?a2:a1;
	ans.maxSum = max(a1.maxSuff + a2.maxPre , max(a1.maxSum, a2.maxSum));
	ans.maxPre = max(a1.maxPre, a1.total + a2.maxPre);
	ans.maxSuff = max(a1.maxSuff + a2.total,a2.maxSuff);
	ans.total = a1.total + a2.total; 
	return ans;
}

int main()
{
	int n,m,x,y;
	cin >> n;
	int *arr = new int[n];
	for(int i=0;i<n;i++) cin >> arr[i];
	node *tree = new node[4*n]();
	buildTree(arr,tree,0,n-1,1);
	cin >> m;
	while(m--)
	{
		cin >> x >> y;
		x--, y--;
		cout << query(tree,0,n-1,1,x,y).maxSum << "\n";
	}
	return 0;
}