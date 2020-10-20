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

int getCount(vector<int> &nums,int x)
{
	int left = 0, right = 1, ans = 0, n = nums.size();
	while(right < n){
		int value = nums[right] - nums[left];
		if(value <= x){
			ans += right - left;
			right++;
		}
		else if(value > x){
			left++;
		}
	}

	return ans;
}

int smallestPairDistance(vector<int> &nums,int k){

	sort(nums.begin(), nums.end());

	int n = nums.size(), minDiff = INT_MAX, maxDiff = nums[n-1] - nums[0];
	for(int i=1;i<n;i++){
		minDiff = min(minDiff, nums[i] - nums[i-1]);
	}

	while(minDiff <= maxDiff){

		int x = (minDiff + maxDiff)/2;
		int count = getCount(nums, x), c2 = getCount(nums, x - 1);
		cout << x << " " << count << "\n";

		if(c2 < k && k <= count) return x;

		if(k <= count) maxDiff = x - 1;
		else minDiff = x + 1;
	}
	
	return -1;

}

int main(){
	int n, k;
	cin >> n;
	vector<int> nums(n);
	for(int &a: nums) cin >> a;
	cin >> k;
	cout << smallestPairDistance(nums, k) << "\n";	
	return 0;
}

