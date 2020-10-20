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


int getCount(vb &visited,int value,int n){
	int count = 0;
	for(int i = 1;i <= n;i++) if(visited[i] && i > value) count++;

	return count;
}

int kInversePairs(int n,int k,vb visited,int idx = 0,int maxValue = 0){

	if(idx == n){
		return k == 0;
	}
	int ans = 0;
	//Here 1 to n can come
	for(int i = 1;i <= n;i++){
		if(!visited[i]){
			if(i > maxValue){
				visited[i] = true;
				ans += kInversePairs(n, k, visited, idx + 1, max(i, maxValue));
				visited[i] = false;
			}
			else{
				int count = getCount(visited, i, n);
				if(k >= count){
					visited[i] = true;
					ans += kInversePairs(n, k - count, visited, idx + 1, maxValue);
					visited[i] = false;
				}
			}
		}
	}

	
	return ans;
}


int kInversePairs2(int n,int k){
	ll bigM = 1e9 + 7;
	vvi dp(n + 1, vi(k + 1, 0));
	for(int i = 0;i <= n;i++) dp[i][0] = 1;
	int maxr = 0;
	for(int i = 2;i <= n;i++){
		maxr += (i - 1);
		for(int j = 1;j <= min(maxr, k);j++){
			dp[i][j] = (dp[i-1][j] + (ll)dp[i][j-1])%bigM;
			if(j >= i){
				dp[i][j] = ((ll)dp[i][j] - dp[i-1][j-i] + bigM)%bigM;
			}
		}
	}

	return dp[n][k];
}


int kInversePairs3(int n,int k){
	if(k == 0) return 1;
	vvi dp(2, vi(k + 1, 0));
	dp[0][0] = 1, dp[1][0] = 1;
	int maxr = 0, curr = 1;
	ll bigM = 1e9 + 7;
	for(int i = 2;i <= n;i++){
		maxr += (i - 1);
		for(int j = 1;j <= min(maxr, k);j++){
			dp[curr][j] = (dp[curr^1][j] + (ll)dp[curr][j - 1])%bigM;
			if(j >= i){
				dp[curr][j] = ((ll)dp[curr][j] - dp[curr^1][j - i] + bigM)%bigM;
			}
		}
		curr ^= 1;
	}

	return dp[curr^1][k];
}



int main(){
	int n, k;
	cin >> n >> k;
	vb visited(n + 1, false);
	cout << kInversePairs3(n, k) << "\n";
	return 0;
}


