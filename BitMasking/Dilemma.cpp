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
#define vvi vector<vector<int> >
#define vvb vector<vector<bool> >
#define vs vector<string>
#define N 1000000

bool oneBitSet(int mask,int n)
{
	int count = 0;
	rep(i,0,n)
	{
		if((mask&(1<<i))) count++;
	}
	return count <= 1;
}

int minTouches(int mask,vs &s,int l,int **dp,int pos = 0)
{
	if(((mask & (mask-1)) == 0) || (mask == 0)) return 0;//	Checking 1 bit set
	if(pos >= l) return INT_MAX;
	if(dp[pos][mask] != -1) return dp[pos][mask];
	int newmask0 = 0, newmask1 = 0, numSet = 0;
	rep(i,0,s.size())
	{
		if((mask&(1<<i)) == 0) continue;//Means this index string has already been taken care of
		if(s[i][pos] == '1') newmask1 = newmask1 | (1<<i);
		else newmask0 = newmask0 | (1<<i);
		numSet += 1;
	}
	int &ans = dp[pos][mask];
	ans = INT_MAX;
	if(newmask0 != 0 && newmask1 != 0)
	{
		int a1 = minTouches(newmask0, s, l, dp, pos+1);
		int a2 = minTouches(newmask1, s, l, dp, pos+1);
		if(a1 == INT_MAX || a2 == INT_MAX) ans = INT_MAX;
		else ans = a1+a2+numSet;
	}

	ans = min(ans, minTouches(mask, s, l, dp, pos+1));
	return dp[pos][mask];
}

int main()
{
	int n;
	cin >> n;
	vs s(n);
	for(string &k: s) cin >> k;
	int mask = (1<<n)-1, l = s[0].size();
	int **dp = new int*[l];
	rep(i,0,l)
	{
		dp[i] = new int[(1<<n)];
		fill(dp[i], dp[i] + (1<<n), -1);
	}
	cout << minTouches(mask, s, l,dp) << "\n";
	rep(i,0,l) delete []dp[i];
	delete []dp;
	return 0;
}