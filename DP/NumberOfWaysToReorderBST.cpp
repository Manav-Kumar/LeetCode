#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <cmath>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vmp vector<map<int,int> >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvmp vector<vmp>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define ll long long

ll mod = 1e9 + 7;

class node{
public:
	int val;
	node* left;
	node* right;
	node(int v = 0): val(v), left(NULL), right(NULL) {}

	~node(){
		delete left;
		delete right;
	}
};

node* insert(node* root,int val){
	if(!root){
		return new node(val);
	}
	if(val < root->val) root->left = insert(root->left, val);
	else root->right = insert(root->right, val);
	return root;
}


int getCount(int n, int m,vvi &dp){
	if(dp[n][m] != -1) return dp[n][m];
	if(m == 0 || n == 0){
		return dp[n][m] = 1;
	}
	return dp[n][m] = (getCount(n - 1,m, dp)%mod + getCount(n, m - 1, dp)%mod)%mod;
}

pair<int,ll> helper(node* root, vvi &dp)
{
	if(!root) return pair<int,int> (0,1);
	pair<int,ll> a1 = helper(root->left, dp);
	pair<int,ll> a2 = helper(root->right, dp);
	pair<int,ll> ans(a1.first + a2.first + 1, 0);
	ans.second = (((getCount(a1.first, a2.first, dp)*a1.second)%mod)*a2.second)%mod;
	return ans;
}

int numOfWays(vi &nums)
{
	int n = nums.size();
	node* root = NULL;
	for(int i = 0;i < n;i++){
		root = insert(root, nums[i]);
	}
	vvi dp(101, vi(101, -1));
	int ans = helper(root, dp).second;
	delete root;
	return ans - 1;
}

int main(){
	int n;
	cin >> n;
	vi nums(n);
	for(int &a: nums) cin >> a;
	cout << numOfWays(nums) << "\n";
	return 0;
}




