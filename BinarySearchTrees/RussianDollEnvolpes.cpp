#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <list>
using namespace std;

#define vb vector<bool>
#define vi vector<int>
#define vvb vector<vb>
#define vvi vector<vi>

bool compare(vector<int> &a,vector<int> &b){

	if(a[0]!=b[0]) return a[0] < b[0];
	return a[1] > b[1];
}

int helper(vvi &envelopes,int idx = 0,int h = -1, int w = -1){

	if(idx == envelopes.size()){
		return 0;
	}

	int a1 = helper(envelopes, idx + 1, h, w);
	int a2 = INT_MIN;
	if(h == -1 || (envelopes[idx][0] > h && envelopes[idx][1] > w)){
		a2 = helper(envelopes, idx + 1, envelopes[idx][0], envelopes[idx][1]) + 1;
	}

	return max(a1, a2);

}

int binarySearch(vector<int> &A,int value)
{
	int st = 0, en = A.size() - 1, ans = -1;
	if(A.size() == 0 || value > A[en]) return A.size();
	while(st <= en){
		int mid = (st + en)/2;
		if(A[mid] == value) return mid;
		else if(value < A[mid]){
			ans = mid;
			en = mid - 1;
		}
		else if(value > A[mid]){
			st = mid + 1;
		}
	}
	return ans;
}


int maxEnvolpes(vector<vector<int> >& envelopes)
{
	sort(envelopes.begin(), envelopes.end(), compare);
	//int ans = helper(envelopes);
	vector<int> dp;
	for(int i = 0;i < envelopes.size();i++){

		int idx = binarySearch(dp, envelopes[i][1]);
		if(idx == dp.size()) dp.push_back(envelopes[i][1]);
		else dp[idx] = envelopes[i][1];
	}

	return dp.size();
}

int main(){
	int n;
	cin >> n;
	vvi envelopes(n, vi(2));
	for(vi &a: envelopes){
		cin >> a[0] >> a[1];
	}
	cout << maxEnvolpes(envelopes) << "\n";
	return 0;
}





