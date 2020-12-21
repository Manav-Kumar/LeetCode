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

ll mod = 1e9 + 7;


int numSubseq2(vector<int> &nums,int target){

	long long power[10001];
	power[0] = 1;
	for(int i=1;i<=10000;i++) power[i] = (power[i - 1]*2)%mod;

	ll ans = 0;
	sort(nums.begin(), nums.end());
	int n = nums.size(), i = 0, j = n - 1;
	while(i <= j){
		if(nums[i] + nums[j] <= target) ans += power[j - i], i++;
		else j--;
		ans %= mod;
	}
	return ans;
}

int longestSubarray(vector<int> &nums, int limit){
	priority_queue<pair<int,int> > pqmax;
	priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pqmin;
	int i = 0, j = 0, len = 0, maxlen = 0, n = nums.size();
	while(j < n){
		pqmin.push({nums[j], j}), pqmax.push({nums[j], j});

		while(pqmin.top().second < i) pqmin.pop();
		while(pqmax.top().second < i) pqmax.pop();

		cout << i << " " << j << " " << pqmax.top().first << " " << pqmin.top().first << "\n";

		if(pqmax.top().first - pqmin.top().first <= limit) maxlen = max(maxlen, j - i + 1), j++;
		else i++;

		if(j < i) j = i;

	}
	return maxlen;
}


int main(){
	int n, target;
	cin >> n >> target;
	vector<int> nums(n);
	for(int &a: nums) cin >> a;
	cout <<longestSubarray(nums, target) << "\n";
	return 0;
}

