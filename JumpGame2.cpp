#include <iostream>
#include <vector>
using namespace std;

void update(long long *tree,int index,long long val,int st,int en,int treeNode = 1)
{
	if(st == en)
	{
		tree[treeNode] = val;
		return ;
	}
	int mid = (st + en)/2;
	if(index <= mid) update(tree, index, val, st, mid, 2*treeNode);
	else update(tree, index, val, mid+1, en, 2*treeNode+1);
	tree[treeNode] = min(tree[2*treeNode], tree[2*treeNode+1]);
	return;
}

long long Query(long long *tree,int left,int right,int st,int en,int treeNode = 1)
{
	//Completely Outside
	if(left > en || right < st || st > en) return INT_MAX;
	//Completely Inside
	if(left <= st && right >= en) return tree[treeNode];
	//Partially
	int mid = (st + en)/2;
	long long a1 = Query(tree,left, right, st, mid, 2*treeNode);
	long long a2 = Query(tree, left, right, mid+1, en, 2*treeNode+1);
	return min(a1,a2);
}


int jump(vector<int>& nums)
{
	int n = nums.size();
	long long *tree = new long long[3*n];
	fill(tree, tree + 3*n, INT_MAX);
	long long *dp = new long long[n]();
	dp[n-1] = 0;
	update(tree, n-1, 0, 0, n-1);
	for(int i = n-2;i >= 0;i--)
	{
		dp[i] = Query(tree, i+1,i + nums[i],0,n-1) + 1;
		cout << dp[i] << " ";
		update(tree, i, dp[i], 0, n-1);
	}
	int ans = dp[0];
	delete []dp;
	return ans;
}


int Jump2(vector<int>& nums)
{
	int n = nums.size();
	int maxReachPos = nums[0];
	int curMaxReachPos = nums[0];
	int curStep = 1;
	for(int i = 1;i <= min(n, maxReachPos);i++)
	{
		curMaxReachPos = max(curMaxReachPos, i + nums[i]);
		if(i == n-1) return curStep;
		if(i == maxReachPos)
		{
			curStep++;
			maxReachPos = curMaxReachPos;
		}
	}
	return 0;
}


void update2(bool *tree,int index,int st,int en,int treeNode = 1)
{
	if(st == en)
	{
		tree[treeNode] = true;
		return ;
	}
	int mid = (st + en)/2;
	if(index <= mid) update2(tree, index, st, mid, 2*treeNode);
	else update2(tree, index, mid+1, en, 2*treeNode+1);
	tree[treeNode] = tree[2*treeNode]||tree[2*treeNode+1];
	return;
}

bool Query2(bool *tree,int left,int right,int st,int en,int treeNode = 1)
{
	//Completely Outside
	if(left > en || right < st || st > en) return false;
	//Completely Inside
	if(left <= st && right >= en) return tree[treeNode];
	//Partially
	int mid = (st + en)/2;
	bool a1 = Query2(tree,left, right, st, mid, 2*treeNode);
	bool a2 = Query2(tree, left, right, mid+1, en, 2*treeNode+1);
	return (a1||a2);
}


bool canJump(vector<int>& nums)
{
	int n = nums.size();
	bool *tree = new bool[3*n];
	fill(tree, tree + 3*n, false);
	bool *dp = new bool[n]();
	dp[n-1] = true;
	update2(tree, n-1, 0,n-1);
	for(int i = n-2;i >= 0;i--)
	{
		dp[i] = Query2(tree, i, i + nums[i], 0,n -1);
		if(dp[i]) update2(tree, i, 0, n-1);
	}
	bool ans = dp[0];
	delete []tree;
	delete []dp;
	return ans;
}

bool canJump2(vector<int>& nums)
{
	int n = nums.size();
	int maxReachPos = nums[0], curMaxReachPos = nums[0];
	bool *dp = new bool[n]();
	fill(dp, dp + n, false);
	dp[0] = true;
	for(int i = 1;i <= min(n-1, maxReachPos);i++)
	{
		dp[i] = true;
		curMaxReachPos = max(curMaxReachPos, i + nums[i]);
		if(i == maxReachPos) maxReachPos = curMaxReachPos;
	}
	bool ans = dp[n-1];
	delete []dp;
	return ans;
}

int main()
{
	int n;
	vector<int> nums;
	cin >> n;
	nums.resize(n);
	for(int &a: nums) cin >> a;
	cout << Jump2(nums) << endl;
	return 0;
}