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
#define vvb vector<vb>
#define vvi vector<vi>


// int getValue(vector<int> &nums,int st,int en,int size){

// 	int i = st, j = i + size - 1, ans = INT_MIN, curr = 0;
// 	for(int k=i;k<=j && k <= en;k++) curr += nums[k];

// 	while(j <= en){
// 		ans = max(ans, curr);
// 		curr -= nums[i];
// 		i++, j++;
// 		if(j <= en) curr += nums[j];
// 	}

// 	return ans;
// }

// int helper(vector<int> &nums,int size,int m)
// {
// 	int n = nums.size(), i = 0, j = size - 1, ans = INT_MAX, curr = 0;

// 	for(int k=i;k<=j && k < n;k++) curr += nums[k];
// 	while(j < n){

// 		int t1 = getValue(nums, 0, i-1, n - size - (m-2));
// 		int t2 = getValue(nums, j + 1, n-1, n - size - (m-2));

// 		t1 = max(t1, t2);

// 		if(i < (n - size - (m-2))){
// 			for(int k=0;k<i;k++) t1 = max(t1, nums[k]);
// 		}

// 		if((n - 1 - j) < (n - size - (m-2))){
// 			for(int k=j+1;k<n;k++) t1 = max(t1, nums[k]);
// 		}

// 		cout << size << " " << curr << " " << t1 << "\n";
// 		if(curr >= t1 && ans >= curr && t1 != INT_MIN){
// 			ans = curr;
// 		}
// 		curr -= nums[i];
// 		i++, j++;
// 		if(j < n) curr += nums[j];
// 	}

// 	return ans;
// }

int split(vector<int> &nums,int largestSum){
	int curr = 0, pieces = 1;
	for(int &a: nums){
		if(curr + a > largestSum){
			pieces++;
			curr = a;
		}
		else curr += a;
	}

	return pieces;
}

int splitArray(vector<int> &nums,int m)
{
	int sum = 0, maxele = 0;
	for(int &a: nums){
		sum += a;
		maxele = max(maxele, a);
	}

	int lo = maxele, hi = sum;
	while(lo < hi){
		int mid = (lo + hi)/2;
		int pieces = split(nums, mid);
		if(m < pieces){
			lo = mid + 1;
		}
		else hi = mid;
	}
	return lo;
}


int splitArray2(vector<int> &nums, int m){
	int n = nums.size();
	vi helper(n,0);
	helper[0] = nums[0];
	for(int i=1;i<n;i++) helper[i] = helper[i-1] + nums[i];

	vvi dp(n, vi(m + 1, INT_MAX));
	
	dp[0][1] = nums[0];
	for(int i=1;i<n;i++) dp[i][1] = dp[i-1][1] + nums[i];

	for(int i=0;i<n;i++){
		for(int j = 2;j <= m;j++){

			for(int k = i-1;k >= 0;k--){
				dp[i][j] = min(dp[i][j], max(dp[k][j-1],  helper[i] - helper[k]));
			}
		}
	}
	return dp[n-1][m];
}

int main(){
	int n, m;
	cin >> n;
	vector<int> nums(n);
	for(int &a: nums) cin >> a;
	cin >> m;
	cout << splitArray2(nums, m) << "\n";
	return 0;
}

