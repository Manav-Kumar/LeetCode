#include <iostream>
#include <vector>
using namespace std;

int BinarySearch(vector<int> &nums,int st,int en,int sum)
{
	int index = -1, temp = st;
	while(st <= en)
	{
		int mid = (st+en)/2;
		if(sum <= nums[mid]) en = mid-1;
		else if(sum > nums[mid])
		{
			index = mid;
			st = mid+1;
		}
	}
	if(index == -1) return 0;
	cout << index << " " << temp << endl;
	return (index - temp + 1);
}

int TriangleNumber(vector<int> nums)
{
	sort(nums.begin(), nums.end());
	int count = 0;
	for(int i = 0;i < nums.size();i++)
	{
		for(int j = i+1;j < nums.size();j++)
		{
			count += BinarySearch(nums, j+1, nums.size()-1,nums[i]+nums[j]);
		}
	}
	return count;
}

//Is match

bool isMatch(string s,string p,int **dp,char prev = '@')
{
	if(s.empty() && p.empty()) return true;
	int n = s.size(), m = p.size();
	if(dp[n][m] != -1) return dp[n][m];
	if(p[0] == '*')
	{
		if(s.size() >= 1 && (s[0] == prev || prev == '.'))
		{
			bool a1 = isMatch(s.substr(1), p, dp, prev);
			bool a2 = isMatch(s.substr(1), p.substr(1), dp);
			if(a1 || a2)
			{
				dp[n][m] = 1;
				return true;
			}
		}
		dp[n][m] = isMatch(s, p.substr(1), dp);
		return dp[n][m];
	}

	if(p.size() >= 2 && p[1] == '*')
	{
		dp[n][m] = int(isMatch(s, p.substr(1), dp, p[0]));
		return dp[n][m];
	}

	if(s.size() >= 1 && (s[0] == p[0] || p[0] == '.'))
	{
		dp[n][m] = int(isMatch(s.substr(1), p.substr(1),dp));
		return dp[n][m];
	}
	dp[n][m] = 0;
	return false;
}

bool isMatch2(string s,string p,int **dp)
{
	if(p.empty()) return s.empty();
	int n = s.size(), m = p.size();
	if(dp[n][m] != -1) return dp[n][m];
	bool first_match = false;
	if(s.size() >= 1 && (s[0] == p[0] || p[0] == '.')) first_match = true;

	if(p.size() >= 2 && p[1] == '*')
	{
		dp[n][m] = isMatch2(s, p.substr(2), dp) || (first_match && isMatch2(s.substr(1), p, dp));
		return dp[n][m];
	}
	else
	{
		dp[n][m] = (first_match && isMatch2(s.substr(1), p.substr(1), dp));
		return dp[n][m];
	}
}


int main()
{
	string s,p;
	cin >> s >> p;
	int **dp = new int*[s.size()+1];
	for(int i = 0;i <= s.size();i++)
	{
		dp[i] = new int[p.size()+1];
		fill(dp[i], dp[i] + p.size()+1, -1);
	}
	cout << isMatch(s,p,dp) << endl;
	return 0;
}