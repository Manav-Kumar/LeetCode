#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <cmath>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vvvvi vector<vvvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define ll long long


int helper2(vvi &cost, vvvvi &dp, int idx,int v1,int v2)
{
	if(idx == cost[0].size()){
		int n = cost.size(), m = cost[0].size();
		if(v1 == int((1<<n) - 1) && v2 == int((1<<m) - 1)) return 0;
		return 10000;
	}
	int &finalAns = dp[v1][v2][idx][1];
	if(finalAns != -1) return finalAns;
	int ans = helper2(cost, dp, idx + 1, v1, v2);
	v2 |= (1<<idx);
	for(int i = 0;i < cost.size();i++){
		ans = min(ans, helper2(cost, dp, idx + 1, v1 | (1<<i) , v2) + cost[i][idx]);
	}
	finalAns = ans;
	return ans;
}

int helper1(vvi &cost,vvvvi &dp, int idx = 0,int v1 = 0, int v2 = 0)
{
	if(idx == cost.size()){
		return helper2(cost, dp, 0, v1, v2);
	}
	int &finalAns = dp[v1][v2][idx][0];
	if(finalAns != -1) return finalAns;
	int ans = helper1(cost, dp, idx + 1, v1, v2);
	v1 |= (1<<idx);
	for(int j = 0;j < cost[0].size();j++){
		ans = min(ans , helper1(cost, dp, idx + 1, v1, v2 | (1<<j)) + cost[idx][j]);
	}
	finalAns = ans;
	return ans;
}

int connectTwoGroups(vvi &cost)
{
	int n = cost.size(), m = cost[0].size();
	vvvvi dp((1<<n), vvvi((1<<m), vvi(12, vi(2, -1))));
	return helper1(cost, dp);
}



int connectTwoGroups2Helper(vvi &cost,vvi &dp, int idx = 0,int state = 0)
{
	int n = cost.size(), m = cost[0].size(), m2 = (1<<m) - 1;
	if(idx == n){
		if(state == m2) return 0;
		return 99999;
	}
	int &finalAns = dp[idx][state];
	if(finalAns != -1) return finalAns;
	int ans = INT_MAX;
	for(int j = 1;j <= m2;j++){
		int curCost = 0;
		for(int id = 0;int(1<<id) <= j ;id++){
			if((j&(1<<id)) > 0){
				curCost += cost[idx][id];
			}
		}
		ans = min(ans, curCost + connectTwoGroups2Helper(cost, dp, idx + 1, state | j));
	}
	finalAns = ans;
	return ans;

}

int connectTwoGroups2(vvi &cost)
{
	int n = cost.size(), m = cost[0].size(), m2 = (1<<m) - 1;
	vvi dp(n, vi(m2 + 1, -1));
	return connectTwoGroups2Helper(cost, dp);
}

int connectTwoGroups3Helper(vvi &cost,vvi &dp, int idx = 0,int state = 0)
{
	int n = cost.size(), m = cost[0].size(), m2 = (1<<m) - 1;
	if(idx == n){
		if(state == m2) return 0;
		return 99999;
	}

	int &finalAns = dp[idx][state];
	if(finalAns != -1) return finalAns;
	int ans = INT_MAX;
	for(int j = 0;j < m;j++){
		if((state&(1<<j)) > 0) ans = min(ans, cost[idx][j] + connectTwoGroups3Helper(cost, dp, idx + 1, state)); 
	}

	int subset = (~(state) & m2);
	for(int i = subset;i > 0;i = (i - 1)&subset){
		int curCost = 0;
		for(int id = 0;int(1<<id) <= i;id++){
			if((i&(1<<id)) > 0){
				curCost += cost[idx][id];
			}
		}
		ans = min(ans, curCost + connectTwoGroups3Helper(cost, dp, idx + 1, state | i));
	}
	finalAns = ans;
	return ans;

}

int connectTwoGroups3(vvi &cost){
	int n = cost.size(), m = cost[0].size(), m2 = (1<<m) - 1;
	vvi dp(n, vi(m2 + 1, -1));
	return connectTwoGroups3Helper(cost, dp);

}


int connectTwoGroups4Helper(vvi &cost, vvi &dp,vi &min_sz2, int idx = 0,int state = 0)
{
	int n = cost.size(), m = cost[0].size(), m2 = (1 << m) - 1;
	if(idx == n){
		int take = 0;
		for(int j = 0;j < m;j++){
			if((state&(1<<j)) == 0) take += min_sz2[j];
		}
		return dp[idx][state] = take;
	}

	int &finalAns = dp[idx][state];
	if(finalAns != -1) return finalAns;

	int ans = INT_MAX;
	for(int j = 0;j < m;j++){
		ans = min(ans, cost[idx][j] + connectTwoGroups4Helper(cost, dp, min_sz2, idx + 1, state | (1<<j)));
	}
	finalAns = ans;
	return ans;
}

int connectTwoGroups4(vvi &cost){
	int n = cost.size(), m = cost[0].size(), m2 = (1<<m) - 1;
	vvi dp(n + 1, vi(m2 + 1, -1));
	vector<int> min_sz2(m, INT_MAX);
	for(int j = 0;j < m;j++){
		for(int i = 0;i < n;i++){
			min_sz2[j] = min(min_sz2[j], cost[i][j]);
		}
	}
	return connectTwoGroups4Helper(cost, dp, min_sz2);
}


int main(){
	int n, m;
	cin >> n >> m;
	vvi cost(n, vi(m, 0));
	for(vi &a: cost) for(int &b: a) cin >> b;
	cout << connectTwoGroups4(cost) << "\n";
	return 0;
}


