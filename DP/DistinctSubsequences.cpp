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


//Count distinct Subs of S which is equal to T

int helper(string s,string t,map<char,vi> &mpS,vvi &dp,int idxT = 0,int idxS = 0)
{
	if(idxT == t.size()) return 1;
	if(idxS == s.size()) return 0;
	if(dp[idxS][idxT] != -1) return dp[idxS][idxT];
	int ans = 0;
	for(int &index: mpS[t[idxT]])
	{
		if(index < idxS) continue;
		ans += helper(s,t,mpS,dp,idxT+1,index+1);
	}
	dp[idxS][idxT] = ans;
	return ans;
}


int numDistinct(string s,string t)
{
	int n = s.size(), m = t.size();
	map<char,vi> mpS;
	for(int i=0;i<s.size();i++) mpS[s[i]].pb(i);
	vvi dp = vvi(n, vi(m, -1));
	int ans = helper(s,t,mpS,dp);
	return ans;
}

int numDistinctLittleDiff(string s,string t,int idxS = 0,int idxT = 0)
{
	if(idxT == t.size()) return 1;
	if(idxS == s.size()) return 0;
	int ans = 0;
	if(s[idxS] == t[idxT]) ans += numDistinctLittleDiff(s,t,idxS+1,idxT+1);
	ans += numDistinctLittleDiff(s,t,idxS+1,idxT);
	return ans;
}

//Iterative Method
int numDistinctIterative(string s,string t)
{
	int n = s.size(), m = t.size();
	vvll dp = vvll(n+1, vll(m+1,0));
	for(int i=m;i>=0;i--) dp[n][i] = 0;
	for(int i=n;i>=0;i--) dp[i][m] = 1;
	for(int i=n-1;i>=0;i--)
	{
		for(int j=m-1;j>=0;j--)
		{
			if(s[i] == t[j]) dp[i][j] += dp[i+1][j+1];
			dp[i][j] += dp[i+1][j];
		}
	}
	int ans = dp[0][0];
	return ans;
}

//Count the Number of Distinct Subsequences
ll mod = pow(10,9) + 7;
int distinctSubseq2(string s)
{
	map<char,ll> mp;
	ll curr = 1;
	for(int i=s.size()-1;i>=0;i--)
	{
		ll temp = curr;
		curr = (curr*2)%mod;
		curr = ((curr - mp[s[i]])%mod + mod)%mod;
		mp[s[i]] = temp;
	}
	return ((curr-1)%mod+mod)%mod;
}

int main()
{
	string s;
	cin >> s;
	cout << distinctSubseq2(s) << "\n";
	return 0;
}

