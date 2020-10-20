#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <cmath>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back

//	O(n^2) ----> DP Approach
int findNumberOfLIS(vector<int>& nums)
{
	int n = nums.size();
	if(n == 0) return 0;
	pair<int,int> *dp = new pair<int,int>[n];
	int maxCount = 1, count = 0;
	dp[0].first = 1, dp[0].second = 1;
	rep(i,1,n)
	{
		int temp = 1;
		dp[i].first = 0;
		repR(j,i-1,0)
		{
			if(nums[i] > nums[j])
			{
				if(dp[i].first < dp[j].first)
				{
					temp = dp[j].second;
					dp[i].first = dp[j].first;
				}
				else if(dp[i].first == dp[j].first) temp += dp[j].second;
			}
		}
		dp[i].first += 1;
		dp[i].second = temp;
		maxCount = max(maxCount, dp[i].first);
	}
	rep(i,0,n)
	{
		cout << dp[i].first << " " << dp[i].second << "\n";
		if(dp[i].first == maxCount) count += dp[i].second;
	}
	return count;
}


//	O(n*log(n)) -----> Segment Tree
int findNumberOfLIS2(vector<int>& nums)
{
	//	Coordinate Compression
	unordered_set<int> s(nums.begin(), nums.end());
	map<int,int> mp;
	int count = 0;
	for(auto it = s.begin();it != s.end();it++,count++) mp[*it] = count;
	vector<int> arr(nums.size(),0);
	rep(i,0,nums.size()) arr[i] = mp[nums[i]];

	return 0;
}

int main()
{
	vector<int> nums;
	int n;
	cin >> n;
	nums.resize(n);
	for(int &a: nums) cin >> a;
	cout << findNumberOfLIS(nums) << "\n";
	return 0;
}




