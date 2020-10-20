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
#define N 1000000

bool isSpatial(int n,int masked,int index)
{
	rep(i,0,n)
	{
		if(i == index || ((masked>>i)&1) == 0) continue;
		if(((i+1)&(index+1)) == (index+1)) return false;  
	}
	return true;
}

int helper(int n,int masked,int *dp)
{
	if(masked == (1<<n)-1) return 1;//Means every number has been assigned
	if(dp[masked] != -1) return dp[masked];
	int ans = 0;
	rep(i,0,n)
	{
		if(((masked>>i)&1) == 0 && isSpatial(n,masked, i))//This means this bit/index number is not yet assigned
		{
			masked = masked|(1<<i);
			ans += helper(n,masked, dp);
			masked = masked&(~(1<<i));
		}
	}
	dp[masked] = ans;
	return ans;
}

int CountSpecialPermu(int n)
{
	int masked = 0, maxNumber = (1<<n)-1;
	int *dp = new int[maxNumber+1];
	fill(dp, dp + maxNumber+1, -1);
	int ans = helper(n,masked,dp);
	delete []dp;
	return ans;
}

//	1 Indexing

ll rect(int mask,int n)
{
	if(mask == (1<<(n+1))-2) return 1;
	ll ans = 0;
	for(int i=1;i<=n;i++)
	{
		if(!(mask&(1<<i)))
		{
			bool ok = true;
			rep(j,1,n+1)
			{
				if(j == i || ((mask>>j)&1) == 0) continue;
				if((i&j) == i) ok = false; 
			}
			if(!ok) continue;
			ans += rect(mask | (1<<i));
		}
	}
	return ans;
}

//Iteratively
int Iteratively(int n)
{
	int *dp = new int[(1<<n)];
	dp[0] = 1;

	for(int mask = 0;mask < (1<<n);mask++)
	{
		rep(i,0,n)
		{
			if(((mask>>i)&1) == 1 && isSpatial(n,mask, i))
			{
				dp[mask] += dp[mask&(~(1<<i))];
			}
		}
	}
	int ans = dp[(1<<n)-1];
	delete []dp;
	return ans;
}

int main()
{
	vector<
	int n;
	cin >> n;
	cout << CountSpecialPermu(n) << "\n";
	return 0;
}

