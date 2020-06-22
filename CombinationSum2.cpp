#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_map>

using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define rep(i,a,b) for(int i=a;i<b;i++)

void helper(vector<vector<int>>& ans,vector<int>& nums,vector<int>& ret,int vis = 0)
{
    if(vis == (1<<nums.size())-1) 
    {
    	ans.push_back(ret);
    	return;
    }
    for(int i = 0;i<nums.size();i++)
    {
        if(((vis>>i)&1) == 0)
        {
            vis |= (1<<i);
            ret.push_back(nums[i]);
            helper(ans, nums, ret,  vis);
            vis &= ~(1<<i);
            ret.pop_back();
        }
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> ans;
    vector<int> ret;
    helper(ans, nums, ret);
    return ans;
}

int main()
{
	int n;
	cin >> n;
	vi nums;
	nums.resize(n);
	for(int &a: nums) cin >> a;
	vvi ans = permute(nums);
	for(vi a: ans)
	{
		for(int c: a) cout << c << " ";
		cout << "\n";
	}
	return 0;
}