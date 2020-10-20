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

int helper(string s,string t,int **output)
{
	int m = s.size(), n = t.size();
	if(s.empty() || t.empty()) return 0;
	if(output[m][n] != -1) return output[m][n];
	int ans;
	if(s[0] == t[0]) ans = 1 + helper(s.substr(1), t.substr(1), output);
	else
	{
		int a1 = helper(s.substr(1), t, output);
		int a2 = helper(s, t.substr(1), output);
		ans = max(a1, a2);
	}
	output[m][n] = ans;
	return ans;
}

int LCS(string s,string t)
{
	int m = s.size(), n = t.size();
	int **output = new int*[m+1];
	for(int i=0;i<=m;i++)
	{
		output[i] = new int*[n+1];
		fill(dp[i], dp[i] + n+1,-1);
	}
	int ans = helper(s,t,output);
	for(int i=0;i<=m;i++) delete []dp[i];
	delete []dp;
	return ans;
}

int LCSIterative(char *l1, char *l2)
{
	int m = strlen(l1);
	int n = strlen(l2);
	int **dp = new int*[m+1];
	for(int i=0;i<=m;i++) dp[i] = new int[n+1]();

	//Fill 1st Columns
	for(int i=0;i<=m;i++) dp[i][0] = 0;
	//Fill 1st row
	for(int i=0;i<=n;i++) dp[0][i] = 0;

	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(l1[m - i] == l2[n - j]) dp[i][j] = dp[i-1][j-1];
			else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		}
	}
	int ans = dp[m][n];
	for(int i=0;i<=m;i++) delete []dp[i];
	delete []dp;
	return ans;
}

//	Find the Longest Subsequence of 1 string which is substring of another

int helper2(string x,string y,int i,int j,int **dp)
{
	if(i == x.size() || j == y.size()) return 0;
	if(dp[i][j] != -1) return dp[i][j];
	int ans;
	if(x[i] == y[j]) ans = 1 + helper2(x, y, i+1,j+1,dp);
	else ans = helper2(x,y,i+1,j,dp);
	dp[i][j] = ans;
	return ans;
}

int LongestSubsSubstring2(string x,string y)
{
	int **dp = new int*[x.size()];
	for(int i=0;i<x.size();i++)
	{
		dp[i] = new int[y.size()];
		fill(dp[i], dp[i] + y.size(),-1);
	}
	int best = 0;
	for(int j=0;j<y.size();j++) best = max(best, helper2(x,y,0,j,dp));
	for(int i=0;i<x.size();i++) delete []dp[i];
	delete []dp;
	return best;
}



int LongestSubsSubstring(string x,int i,string y,int j,map<char,vi> &mpS,bool prev,int ***dp)
{
	if(i == x.size() || j == y.size()) return 0;
	if(dp[i][j][prev] != -1) return dp[i][j][prev];
	int ans = 0;
	for(int &index: mpS[y[j]])
	{
		if(index < i) continue;
		ans = max(ans, LongestSubsSubstring(x,index+1,y,j+1,mpS, true, dp) + 1);
	}
	if(x[i] != y[j] && !prev)
	{
		ans = max(ans, LongestSubsSubstring(x,i,y,j+1,mpS, false, dp));
	}
	dp[i][j][prev] = ans;
	return ans;
}

int main()
{
	string s,t;
	cin >> s >> t;
	// map<char,vi> mpS;
	// for(int i=0;i<s.size();i++) mpS[s[i]].pb(i);
	// int ***dp = new int**[s.size()];
	// for(int i=0;i<s.size();i++)
	// {
	// 	dp[i] = new int*[t.size()];
	// 	for(int j=0;j<t.size();j++)
	// 	{
	// 		dp[i][j] = new int[2]();
	// 		fill(dp[i][j], dp[i][j] + 2,-1);
	// 	}
	// }
	// cout << LongestSubsSubstring(s,0,t,0,mpS, false,dp) << "\n";
	// for(int i=0;i<s.size();i++)
	// {
	// 	dp[i] = new int*[t.size()];
	// 	for(int j=0;j<t.size();j++) delete []dp[i][j];
	// 	delete []dp[i];
	// }
	// delete []dp;
	cout << LongestSubsSubstring2(s,t) << "\n";
	return 0;
}



