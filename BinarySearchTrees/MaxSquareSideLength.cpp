#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <list>
#include <queue>
using namespace std;

#define vb vector<bool>
#define vi vector<int>
#define vp vector<pair<int,int> >
#define vvp vector<vp>
#define vvb vector<vb>
#define vvi vector<vi>
#define rep(i,a,b) for(int i=a;i<b;i++)

int getSum(vvi &dp,int i,int j,int ki,int kj){

	if(ki >= dp.size() || kj >= dp[0].size()) return INT_MAX;
	int sum = dp[ki][kj];
	if(i-1 >= 0) sum -= dp[i-1][kj];
	if(j-1 >= 0) sum -= dp[ki][j-1];
	if(i-1 >= 0 && j-1 >= 0) sum += dp[i-1][j-1];
	return sum;
}

int maxSquareSideLength(vvi arr,int threshold){

	int n = arr.size(), m = arr[0].size(), best = 0;


	//	PreComputation
	vvi dp(n, vi(m, 0));
	dp[0][0] = arr[0][0];

	rep(j,1,m) dp[0][j] = dp[0][j-1] + arr[0][j];
	rep(i,1,n) dp[i][0] = dp[i-1][0] + arr[i][0];

	rep(i,1,n){
		rep(j,1,m){
			dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + arr[i][j];
		}
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(arr[i][j] > threshold) continue;
			int lo = best, hi = min(n - i, m - j), ans = -1;
			while(lo <= hi){
				int k = (lo + hi)/2;
				int sum = getSum(dp, i,j, i + k-1, j + k-1);
				if(sum > threshold) hi = k - 1;
				else{
					ans = k;
					lo = k + 1;
				}
				
			}

			best = max(best, ans);
		}
	}

	return best;
}

int main(){
	int n, m, threshold;
	cin >> n >> m;
	vvi nums(n, vi(m));
	for(vi &a: nums){
		for(int &b: a) cin >> b;
	}
	cin >> threshold;
	cout << maxSquareSideLength(nums, threshold) << "\n";
	return 0;
}

