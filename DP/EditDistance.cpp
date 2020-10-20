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

//	Given 2 strings, return minimum number of operations on T to make it similar to S
//		Allowed Operations are Insertion, Deletion, Update/Replace a Character
int EditDistanceHelper(string s,string t)
{
	int m = s.size(), n = t.size();
	//Base Case
	if(s.empty() || t.empty()) return max(s.size(), t.size());
	int ans;
	if(s[0] == t[0]) ans = EditDistanceHelper(s.substr(1), t.substr(1));
	else
	{
		//Insert Operation
		int a1 = EditDistanceHelper(s.substr(1),t) + 1;
		//Delete Operation
		int a2 = EditDistanceHelper(s, t.substr(1)) + 1;
		//Replace Character
		int a3 = EditDistanceHelper(s.substr(1), t.substr(1)) + 1;
		ans = min(a1, min(a2, a3));
	}
	return ans;
}

int EditDistanceIterative(string s,string t)
{
	int m = s.size(), n = t.size();
	int **dp = new int*[m+1];
	for(int i=0;i<=m;i++) dp[i] = new int[n+1];

	for(int i=0;i<=m;i++) dp[i][0] = i;
	for(int i=0;i<=n;i++) dp[0][i] = i;

	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(s[m - i] == t[n - j]) dp[i][j] = dp[i-1][j-1];
			else dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;
		}
	}
	int ans = dp[m][n];
	for(int i=0;i<=m;i++) delete []dp[i];
	delete []dp;
	return ans;
}

int EditDistance(string s,string t)
{

}

int main()
{

	return 0;
}