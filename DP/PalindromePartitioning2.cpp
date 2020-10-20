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

bool isPalindrome(string s,int st,int en)
{
	int i=st,j=en;
	while(i<j)
	{
		if(s[i] != s[j]) return false;
		i++, j--;
	}
	return true;
}

int helper(string s,vvi &dp,int st,int en)
{
	if(dp[st][en] != -1) return dp[st][en];
	if(st == en || isPalindrome(s,st,en))
	{
		dp[st][en] = 0;
		return 0;
	}
	int ans = INT_MAX;
	for(int i=st;i<en;i++)
	{
		int a1=1;
		if(dp[st][i] != -1) a1 += dp[st][i];
		else a1 += helper(s,dp,st,i);
		if(dp[i+1][en] != -1) a1 += dp[i+1][en];
		else a1 += helper(s,dp,i+1,en);
		ans = min(ans, a1);
	}
	dp[st][en] = ans;
	return ans;
}

int minCuts2(string s)
{
	int n = s.size();
	vi dp(n+1,0);
	dp[n] = -1;
	vector<vector<int>>CheckPalindrome(n,vector<int>(n,0));
    for(int i=0;i<n;i++) CheckPalindrome[i][i]=1;
    for(int cl=2;cl<=n;cl++){
        for(int i=0;i<n-cl+1;i++){
            int j=i+cl-1;
            if(cl==2 && s[i]==s[j]) CheckPalindrome[i][j]=true;
            else{
                if(s[i]==s[j] && CheckPalindrome[i+1][j-1]) 
                    CheckPalindrome[i][j]=true;
            }
        }
    }
	for(int i=n-1;i>=0;i--)
	{
		dp[i] = n - i - 1;
		for(int j=i;j<n;j++)
		{
			if(CheckPalindrome[i][j]) dp[i] = min(dp[i], 1 + dp[j+1]);
		}
	}
	return dp[0];
}

int minCuts(string s)
{
	int n = s.size();
	vvi dp = vvi(n, vi(n,-1));
	return helper(s,dp,0,n-1);
}

int main()
{
	string s;
	cin >> s;
	cout << s.size() << "\n";
	cout << minCuts2(s) << "\n";
	return 0;
}


