#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>

int firstMissingPositive(vector<int> &nums){
	//	Smallest Missing Positive Integer
	int ans = 1;
	unordered_map<int,bool> stored;
	set<int> visited;
	for(int n: nums){
		if(n <= 0) continue;
		stored[n] = true;
		while(stored.count(n) > 0 && ans == n){
			ans++, n++;
		}
	}
	return ans;
}

int firstMissingPositive2(vector<int> &nums){
	vector<int> arr(nums.size() + 1);

	for(int &n: nums){
		if(n >= 1 && n <= nums.size()) arr[n] = 1;
	}
	for(int i=1;i<arr.size();i++) if(arr[i] == 0) return i;
	return nums.size() + 1;
}

int main(){
	int n;
	cin >> n;
	vector<int> nums(n);
	for(int &n: nums) cin >> n;
	cout << firstMissingPositive(nums) << "\n";
	return 0;
}


