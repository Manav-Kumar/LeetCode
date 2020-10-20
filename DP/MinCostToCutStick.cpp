#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <cmath>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define ll long long


int helper(vi &partitions,int st,int en, vi &PrevSum, vvi &dp)
{
	if(st == en) return 0;
	int &finalAns = dp[st][en];
	if(finalAns != -1) return finalAns;
	int cost = PrevSum[en] - (st > 0?PrevSum[st - 1]:0);
	int ans = INT_MAX;
	for(int i = st + 1;i <= en;i++){
		int a1 = helper(partitions, st, i - 1, PrevSum, dp) + helper(partitions, i, en, PrevSum, dp);
		ans = min(ans, a1);
	}
	if(ans != INT_MAX) ans += cost;
	finalAns = ans;
	return finalAns;
}


int minCost(int n,vi &cuts){
	sort(cuts.begin(), cuts.end());
	vi partitions(cuts.size() + 1, 0);
	int ct = 0, i = 0;
	for(i = 0;i < cuts.size();i++){
		
		if(i > 0){
			partitions[ct++] = cuts[i] - cuts[i - 1];
		}
		else partitions[ct++] = cuts[i];
	}
	partitions[ct++] = n - cuts[cuts.size() - 1];
	vi PrevSum(ct, 0);
	PrevSum[0] = partitions[0];
	for(int i = 1;i < ct;i++) PrevSum[i] = PrevSum[i - 1] + partitions[i];

	vvi dp(ct, vi(ct, -1));
	return helper(partitions, 0, partitions.size() - 1, PrevSum, dp);
}

int get(vi &cuts,int i,int j, vvi &dp)
{
	if(j == i + 1) return 0;
	int &finalAns = dp[i][j];
	if(finalAns != -1) return finalAns;
	int cost = cuts[j] - cuts[i], ans = INT_MAX;
	for(int k = i + 1;k < j;k++){
		ans = min(ans, get(cuts, i, k, dp) + get(cuts, k, j, dp) + cost);
	}

	finalAns = ans;
	return ans;
}

int minCost2(int n,vi &cuts)
{
	cuts.push_back(0);
	cuts.push_back(n);
	sort(cuts.begin(), cuts.end());
	int m = cuts.size();
	vvi dp(m, vi(m, -1));
	return get(cuts, 0, m - 1, dp);
}

int main(){
	int n, m;
	cin >> n >> m;
	vi cuts(m);
	for(int &a: cuts) cin >> a;
	cout << minCost2(n, cuts) << "\n";
	return 0;
}






