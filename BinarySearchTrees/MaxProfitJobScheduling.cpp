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


class schedule{
public:
	int en, st, pt;
	schedule(int s = 0,int e = 0,int p = 0): st(s), en(e), pt(p) {}
};

bool compare(schedule &a,schedule &b){
	return a.en != b.en? a.en < b.en: a.st < b.st;
}

int helper(vector<schedule> &arr,vvi &visited, int idx = 0,int prevEnd = 0){

	if(idx == arr.size()) return 0;
	int &value = visited[idx][prevEnd];
	if(value != -1) return value;
	int a1 = helper(arr, visited, idx + 1, prevEnd);
	int a2 = INT_MIN;
	if(arr[idx].st >= prevEnd) a2 = helper(arr, visited, idx + 1, arr[idx].en) + arr[idx].pt;

	value = max(a1, a2);
	return value;
}


int getIdx(vector<schedule> &arr,int lo,int hi, int value){

	int ans = -1;
	while(lo <= hi){
		int mid = (lo + hi)/2;
		if(value < arr[mid].en) hi = mid - 1;
		else{
			ans = mid;
			lo = mid + 1;
		}
	}
	return ans;
}

int helper2(vector<schedule> &arr,vi &visited, int idx){

	if(idx < 0) return 0;
	int &a = visited[idx];
	if(a != -1) return a;
	int a1 = helper2(arr, visited, idx - 1);
	int a2 = arr[idx].pt, temp = getIdx(arr, 0, idx - 1, arr[idx].st);
	if(temp != -1){
		a2 += helper2(arr, visited, temp);
	}
	a = max(a1, a2);
	return a;
}

int jobScheduling(vi &startTime, vi &endTime, vi &profit){
	int n = startTime.size();
	vector<schedule> arr(n);
	for(int i=0;i<n;i++){
		arr[i] = schedule(startTime[i], endTime[i], profit[i]);
	}
	sort(arr.begin(), arr.end(), compare);

	vi visited(n, -1);

	return helper2(arr, visited, arr.size() - 1);
}


class CustomFunction{
public:
	int f(int x,int y){
		return x + y;
	}
};

int findSolutionHelper(CustomFunction& customfunction,int x,int z){
	int lo = 1, hi = 1000;
	while(lo <= hi){
		int y = (lo + hi)/2, value = customfunction.f(x, y);
		if(value == z) return y;
		else if(z < value) hi = y-1;
		else if(z > value) lo = y+1;
	}
	return -1;
}

vvi findSolution(CustomFunction& customfunction, int z){

	vvi ans;
	for(int x = 1;x <= 1000;x++){

		int idx = findSolutionHelper(customfunction, x, z);
		if(idx != -1) ans.push_back(vi {x, idx});
	}

	return ans;

}

//	Smallest Divisor
int getSum(vi &nums,int div){
	int sum = 0;
	for(int &a: nums){
		sum += (a/div) + (a%div == 0?0:1);
	}
	return sum;
}
int SmallestDivisor(vi &nums,int threshold){
	int lo = 1, hi = 0, ans = INT_MAX;
	for(int &a: nums) hi = max(hi, a);

	while(lo <= hi){
		int div = (lo + hi)/2;
		int sum = getSum(nums, div);
		if(sum <= threshold){
			ans = div;
			hi = div - 1;
		}
		else if(sum > threshold){
			lo = div + 1;
		}
	}
	return ans;
}




int main(){
	int n, m, threshold;
	cin >> n >> m;
	vvi nums(n, vi(m));
	for(vi &a: nums){
		for(int &b: a) cin >> b;
	}
	cin >> threshold;
	cout << maxSideLength(nums, threshold) << "\n";
	return 0;
}








