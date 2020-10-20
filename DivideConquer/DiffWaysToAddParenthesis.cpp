#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <unordered_map>
#include <set>
#include <iomanip>
#include <cmath>
#include <math.h>
#include <unordered_set>
#include <climits>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vll vector<ll>
#define vi vector<int>
#define vvi vector<vi >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>


vector<int> diffWaysToCompute(string input,int st, int en){

	vi ans;
	for(int i = st;i <= en;i++){
		if(input[i] == '+' || input[i] == '-' || input[i] == '*'){
			char c = input[i];
			vi a1 = diffWaysToCompute(input, st, i - 1);
			vi a2 = diffWaysToCompute(input, i + 1, en);
			for(int &a: a1){
				for(int &b: a2){
					if(c == '+') ans.push_back(a + b);
					else if(c == '*') ans.push_back(a*b);
					else if(c == '-') ans.push_back(a - b);
				}
			}
		}
	}
	if(ans.empty()){
		int v = 0;
		for(int i = st;i <= en;i++) v = v*10 + int(input[i] - '0');
		ans.push_back(v);
	}
	return ans;
}

//	Kth Largest Element In an Array

int findKthLargest(vi &nums,int k){
	priority_queue<int> pq(nums.begin(),nums.end());
	for(int i=1;i<k;++i) pq.pop();
	return pq.top();
}


//	Beautiful Array

bool BeautifulArrayHelper(vi &ans, vb &visited,map<pair<vb,int>, bool> &mp, int idx = 0){
	int n = ans.size();
	if(idx == n) return true;

	if(mp.count(pair<vb,int> (visited, idx)) > 0) return mp[pair<vb,int> (visited, idx)];

	for(int k = 1;k <= n;k++){
		if(visited[k]) continue;
		vb temp = visited;
		for(int i = 1;i <= n;i++){
			if(visited[i]){
				int j = 2*k - i;
				if(j >= 1 && j <= n) temp[j] = true;
			}
		}
		temp[k] = true, ans[idx] = k;
		bool check = BeautifulArrayHelper(ans, temp, mp, idx + 1);
		if(check) return true;
	}
	mp[pair<vb,int> (visited, idx)] = false;
	return false;
}

vi BeautifulArray(int n){
	vi ans(n);
	vb visited(n + 1, false);
	map<pair<vb,int>, bool> mp;
	bool check = BeautifulArrayHelper(ans, visited, mp);
	return ans;
}


vi BeautifulArray2(int n){
	if(n <= 2) return n == 1?vi{1}:vi{1,2};
	vi odd = BeautifulArray2((n + 1)/2);
	vi even = BeautifulArray2(n/2);
	vi ans;
	for(int &x: odd) ans.push_back(2*x - 1);
	for(int &x: even) ans.push_back(2*x);

	return ans;
}

int main(){
	int n;
	cin >> n;
	vi ans = BeautifulArray(n);
	for(int &a: ans) cout << a << " ";
	return 0;
}






