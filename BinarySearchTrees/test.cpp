#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <unordered_map>
#include <set>
#include <cmath>
#include <math.h>
#include <unordered_set>
#include <deque>
using namespace std;


#define vll vector<long long>
#define vvll vector<vll >


long long helper(vector<long long> &left,vector<long long> &right,vvll &dp,int idx = 0,int y = 0){

	if(idx == left.size()) return 0;

	if(y == right.size()) return INT_MAX;
	if(dp[idx][y] != -1) return dp[idx][y];
	long long a1 = helper(left, right, dp, idx, y + 1);
	long long a2 = max(helper(left, right, dp, idx + 1,y + 1), abs(left[idx] - right[y]));

	dp[idx][y] = min(a1, a2);
	return dp[idx][y];
}


int helper(vector<int> &left,vector<int> &right){

	vector<pair<int,int> > visited(left.size());
	for(int i=0;i<left.size();i++){
		int lo = 0, hi = right.size() - 1;

		while(hi - lo > 1){
			int mid = (lo + hi)/2;
			if(left[i] < right[mid]) ho = mid;
			else lo = mid;
		}

		int ans = INT_MAX, index = -1;
		while(lo <= hi){
			if(ans > abs(left[i] - right[lo])){
				ans = abs(left[i] - right[lo]);
				index = lo;
			}
			lo++;
		}

		visited[i] = pair<int,int> (ans, index);
	}

	sort(visited.begin(), visited.end());

	


}



long long secretSanta(vector<long long> &left, vector<long long> &right)
{
	sort(left.begin(), left.end());
	sort(right.begin(), right.end());
	if(left.size() < right.size()){
		int n = left.size(), m = right.size();
		vvll dp(n, vll(m, -1));
		return helper(left, right, dp);
	}
	else{
		int n = right.size(), m = left.size();
		vvll dp(n, vll(m, -1));
		return helper(right, left, dp);
	}
}



int main(){
	int p,q;
	cin >> p >> q;
	vector<long long> left(p);
	vector<long long> right(q);
	for(long long &a: left) cin >> a;
	for(long long &a: right) cin >> a;
	cout << secretSanta(left, right) << "\n"; 
	return 0;
}


