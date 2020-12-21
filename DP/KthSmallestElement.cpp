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
#include <climits>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vll vector<ll>
#define vi vector<int>
#define vvi vector<vi >
#define vvvi vector<vvi>
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>


class TreeNode{
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v): val(v), left(NULL), right(NULL) {}
};

pair<int,int> kthSmallest(TreeNode* root, int k){
	if(!root) return pair<int,int> (-1, 0);

	pair<int,int> a1 = kthSmallest(root->left, k);
	if(a1.first != -1) return a1;
	if(a1.second + 1 == k) return {root->val, 1};
	pair<int,int> a2 = kthSmallest(root->right, k - a1.second - 1);
	if(a2.first != -1) return a2;
	return {a2.first, a1.second + a2.second + 1};
}

int kthSmallest2(TreeNode* root,int &k){
	if(!root) return -1;
	int ans = kthSmallest2(root->left, k);
	if(ans != -1) return ans;
	if(k == 1) return root->val;
	k--;
	return kthSmallest2(root->right, k);
}

//	Search In rotated Array
int BinarySearch(vi &nums,int st,int en,int target){
	while(st <= en){
		int mid = (st + en)/2;
		if(nums[mid] == target) return mid;
		if(target > nums[mid]) st = mid + 1;
		else if(target < nums[mid]) en = mid - 1;
	}
	return -1;
}

int search(vi &nums, int target){
	int smallestIdx = -1, n = nums.size(), st = 0, en = n - 1, value = INT_MIN;
	int leftsmallest = nums[0], rightmax = nums[n-1];
	while(st <= en){
		int mid = (st + en)/2;
		if(nums[mid] == target) return mid;
		if(nums[mid] <= rightmax) smallestIdx = mid, en = mid - 1;
		else if(nums[mid] > rightmax) st = mid + 1;
	}

	int a1 = BinarySearch(nums, 0, smallestIdx - 1, target);
	if(a1 != -1) return a1;
	return BinarySearch(nums, smallestIdx, n - 1, target);
}

int main(){

	return 0;
}





