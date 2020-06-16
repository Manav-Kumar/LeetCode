#include <iostream>
#include <vector>
using namespace std;

#define rep(i,a,b) for(int i = a;i < b;i++)
typedef long long ll;

//Fenwick Tree: Stores the maximum ans
ll query(ll *tree,ll *lazy,int st,int en,int treeNode,int left,int right)
{
	if(lazy[treeNode])
	{
		tree[treeNode] = lazy[treeNode];
		if(st!=en)
		{
			lazy[2*treeNode] = lazy[treeNode];
			lazy[2*treeNode+1] = lazy[treeNode];
		}
		lazy[treeNode] = 0;
	}
	if(st >= left && en <= right) return tree[treeNode];
	if(left > en || right < st) return 0;
	int mid = (st+en)/2;
	return max(query(tree, lazy,st,mid, 2*treeNode,left, right), query(tree, lazy, mid+1,en,2*treeNode+1,left,right));
}

void update(ll *tree,ll *lazy,int st,int en,int treeNode,int left,int right,int val)
{
	if(lazy[treeNode])
	{
		tree[treeNode] = lazy[treeNode];
		if(st != en)
		{
			//It's not a leaf node
			lazy[2*treeNode] = lazy[treeNode];
			lazy[2*treeNode + 1] = lazy[treeNode];
		}
		lazy[treeNode] = 0;
	}

	//Completely Inside
	if(st >= left && en <= right)
	{
		tree[treeNode] = val;
		if(st != en)
		{
			lazy[2*treeNode] = val;
			lazy[2*treeNode+1] = val;
		}
		return;
	}
	//Completely Outside
	if(left > en || right < st) return;

	//Partial
	int mid = (st+en)/2;
	update(tree, lazy, st, mid, 2*treeNode,left,right,val);
	update(tree, lazy, mid+1,en,2*treeNode+1,left,right, val);

	tree[treeNode] = max(tree[2*treeNode], tree[2*treeNode+1]);
	return;
}

vector<int> fallingSquares(vector<vector<int> > &positions)
{
	vector<int> a;
	for(vector<int> &p: positions)
	{
		a.push_back(p[0]);
		a.push_back(p[0] + p[1]);
	}
	sort(a.begin(), a.end());
	int n = unique(a.begin(), a.end()) - a.begin();
	//Here instead of taking their absolute values, we are taking their just indices in order
	ll *tree = new ll[n<<2]();
	ll *lazy = new ll[n<<2]();
	//Initializing both below matrices with 0
	vector<int> ans;
	for(const vector<int> &p: positions)
	{
		int l = lower_bound(a.begin(), a.end(), p[0]) - a.begin();
		int r = lower_bound(a.begin(), a.end(), p[0] + p[1]) - a.begin();
		ll maxExistHeight = query(tree, lazy, 0, n, 1, l+1, r);

		maxExistHeight += p[1];
		update(tree, lazy, 0, n, 1, l+1, r, maxExistHeight);
		ans.push_back(max(tree[1], lazy[1]));
	}
	delete []tree;
	delete []lazy;
	return ans;
}

int main()
{
	vector<vector<int> > positions;
	int n;
	cin >> n;
	positions.resize(n);
	for(vector<int> &a: positions)
	{
		a.resize(2);
		cin >> a[0] >> a[1];
	}

	vector<int> ans = fallingSquares(positions);
	for(int a: ans) cout << a << " ";
	return 0;
}

