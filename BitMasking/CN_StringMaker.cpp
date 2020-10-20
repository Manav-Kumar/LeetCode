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

ll mod = pow(10,9) + 7;

ll solve(string A,int i,string B,int j,string C,int z,map<char,vi>& mpA,map<char,vi> &mpB,int ***dp)
{
	if(z < 0) return 1;
	if(dp[i+1][j+1][z+1] != -1) return dp[i+1][j+1][z+1];
	ll ans = 0;
	char curr = C[z];
	for(int &index: mpA[curr])
	{
		if(index > i) break;
		ans = (ans + solve(A,index-1, B, j, C, z-1, mpA, mpB, dp))%mod;
	}

	for(int &index: mpB[curr])
	{
		if(index > j) break;
		ans = (ans + solve(A, i, B, index-1, C, z-1, mpA, mpB, dp))%mod;
	}
	dp[i+1][j+1][z+1] = ans;
	return ans%mod;

}

int main()
{
	string a,b,c;
	cin >> a >> b >> c;
	map<char,vi > mpA, mpB;
	rep(i,0,c.size())
	{
		if(!mpA[c[i]].empty()) continue;
		rep(j,0,a.size())
		{
			if(a[j] == c[i]) mpA[c[i]].pb(j);
		}
		rep(j,0,b.size())
		{
			if(b[j] == c[i]) mpB[c[i]].pb(j);
		}
	}
	int ***dp = new int**[a.size()+1];
	rep(i,0,a.size()+1)
	{
		dp[i] = new int*[b.size()+1];
		rep(j,0,b.size()+1)
		{
			dp[i][j] = new int[c.size()+1];
			fill(dp[i][j], dp[i][j] + c.size() + 1, -1);
		}
	}
	cout << solve(a,a.size()-1,b,b.size()-1,c,c.size()-1,mpA,mpB,dp) << "\n";
	rep(i,0,a.size())
	{
		rep(j,0,b.size()) delete []dp[i][j];
		delete []dp[i];
	}
	delete []dp;
	return 0;
}