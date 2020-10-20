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

int numAP(vector<int> &arr)
{
	int maxCommDiff = 0, minele = INT_MAX, maxele = INT_MIN;
	for(int &a: arr)
	{
		minele = min(minele, a);
		maxele = max(maxele, a);
	}
	maxCommDiff = maxele - minele;
	vvi dp(arr.size(), vi(2002, 0));
	
	repR(i,arr.size()-1,0)
	{
		rep(j,i+1,arr.size())
		{
			dp[i][arr[j] - arr[i] + 1000] += dp[j][arr[j] - arr[i] + 1000] + 1;
		}
	}
	int ans = 0;
	rep(i,0,arr.size())
	{
		ans += 1;
		rep(cd, 0, dp[i].size()) ans += dp[i][cd];
	}
	return ans;
}

int main()
{
	int n;
	cin >> n;
	vector<int> arr(n);
	for(int &a: arr) cin >> a;
	cout << numAP(arr) + 1 << "\n";
	return 0;
}

