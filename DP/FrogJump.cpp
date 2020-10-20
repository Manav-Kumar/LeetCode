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

int isValidJump(int st,int en,int val)
{
	if((en-st) == val) return 0;
	if((en-st) == val-1) return -1;
	if((en-st) == val+1) return 1;
	return -2;
}

int helper(vector<int> &stones,vvi &dp,int prevJump=1,int prevIdx = 0,int idx=0)
{
	if(idx == stones.size()-1) return true;
	if(idx == stones.size()) return false;
	if(dp[idx][prevIdx] != -1) return dp[idx][prevIdx];
	int temp = idx+1;
	while(temp < stones.size())
	{
		int isCorrect = isValidJump(stones[idx], stones[temp++], prevJump);
		if(isCorrect == -2) continue;
		if(helper(stones, dp, prevJump + isCorrect, idx,temp-1))
		{
			dp[idx][prevIdx] = true;
			return true;
		}
	}
	dp[idx][prevIdx] = false;
	return false;
}

bool canCross(vi &stones)
{
	if(stones.size() == 2 && stones[1] != 1) return false;
	vvi dp = vvi(1101, vi((1101),-1));
	return helper(stones, dp);
}

int main()
{
	int n;
	cin >> n;
	vi stones(n);
	for(int &a: stones) cin >> a;
	if(canCross(stones)) cout << "Can Cross" << "\n";
	else cout << "Can Not Cross" << "\n";
	return 0;
}

