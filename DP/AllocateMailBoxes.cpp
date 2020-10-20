#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <cmath>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vmp vector<map<int,int> >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvmp vector<vmp>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define ll long long

ll mod = 1e9 + 7;

int helper(vi &houses,int start,int end, int idx,int k, vvvi &dp, int prev = 0)
{
	if(k == 0){
		int cost = 0;
		for(int &l: houses) if(l >= prev) cost += (l - prev);
		return cost;
	}
	if(idx > end){
		return INT_MAX;
	}

	int &ans = dp[idx - start + 1][k][(prev == 0?0: prev - start + 1)];

	if(ans != -1) return ans;


	int a1 = helper(houses, start, end, idx + 1, k, dp, prev);
	int a2 = helper(houses, start, end, idx + 1,k - 1, dp, idx);

	int cost = 0;
	for(int &l: houses){
		if(l >= prev && l <= idx){
			if(prev == 0) cost += idx - l;
			else cost += min(l - prev, idx - l);
		}
	}
	if(a2 != INT_MAX) a2 += cost;
	ans = min(a1, a2);
	return ans;
}

int minDistance(vi &houses, int k)
{
	sort(houses.begin(), houses.end());
	int n = houses.size(), start = houses[0], end = houses[n - 1], len = end - start + 1;
	vvvi dp(len + 1, vvi(k + 1, vi(len + 1, -1)));
	return helper(houses, start, end, start, k, dp);
}


int minDistance(vi &houses,int idx, int k, vvi &dp)
{
	int n = houses.size();
	if(idx >= n){
		if(k == 0) return 0;
		return INT_MAX;
	}
	if(k == 0){
		dp[idx][k] = 1e9;
		return dp[idx][k];
	}


	if(dp[idx][k] != -1) return dp[idx][k];
	int ans = 1e9, mid = 0, sum = 0;
	for(int j = idx;j < n;j++){
		mid = (idx + j)/2, sum = 0;
		for(int l = idx;l <= j;l++){
			sum += abs(houses[l] - houses[mid]);
		}
		ans = min(ans, minDistance(houses, j + 1,k - 1, dp) + sum);
	}

	dp[idx][k] = ans;
	return ans;
}

int main(){
	int n, k;
	cin >> n;
	vi houses(n);
	for(int &a: houses) cin >> a;
	cin >> k;
	vvi dp(n, vi(k + 1, -1));
	sort(houses.begin(), houses.end());
	cout << minDistance(houses, 0, k, dp) << "\n"; 
	return 0;
}




