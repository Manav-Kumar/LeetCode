#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>

typedef long long ll;

ll mod = 1e6 + 3;
int dp[101][101][2];


int SumAsK(int n,int k,int last){

	if(n == 0) return k == 0;

	if(dp[n][k][last] != -1) return dp[n][k][last];

	int ans = 0;
	//	Current Set as 0
	ans = (ans + SumAsK(n - 1, k, 0))%mod;
	//	Current Set as 1
	if(k == 0 && last == 0){
		ans = (ans + SumAsK(n - 1, k, 1))%mod;
	}
	else if(k > 0) ans = (ans + SumAsK(n - 1, k - last, 1))%mod;
	dp[n][k][last] = ans%mod;
	return ans%mod;
}


int main(){
	int t, n, k;
	for(int i=0;i<101;i++) for(int j=0;j<101;j++) dp[i][j][0] = -1, dp[i][j][1] = -1;
	cin >> t;
	while(t--){
		cin >> n >> k;
		int ans;
		if(n <= k) ans = 0;
		else if(k == n - 1) ans = 1;
		else{
			ans = (SumAsK(n - 1, k, 0) + SumAsK(n - 1, k, 1))%mod;
		}
		cout << ans << "\n";
	}
	return 0;
}
