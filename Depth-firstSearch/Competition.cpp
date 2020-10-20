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
#include <algorithm>
#include <climits>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vi >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>

ll mod = 1e9 + 7;
vector<ll> powers;

void fill(int k){
	powers.clear();
	powers.resize(k + 1, 0);
	powers[0] = 1, powers[1] = 2;
	for(int i = 2;i <= k;i++){
		powers[i] = (powers[i - 1]*2)%mod;
	}
}

int ELamps(int h,int w,vs s){

	ll ans = 0;

	int k = 0;
	rep(i, 0, h) rep(j, 0, w) if(s[i][j] == '.') k++;
	fill(k);

	vvi count(h, vi(w, 0));
	rep(i, 0, h){
		vi lr(w, 0), rl(w, 0);
		rep(j, 0, w){
			if(s[i][j] == '#') continue;
			if(j == 0) lr[j] = 1;
			else lr[j] += lr[j - 1] + 1;
		}
		for(int j = w-1;j >= 0;j--){
			if(s[i][j] == '#') continue;
			if(j == (w - 1)) rl[j] += 1;
			else rl[j] = rl[j + 1] + 1;

			count[i][j] = lr[j] + rl[j] - 1;
		}
	}

	rep(j, 0, w){
		vi ud(h, 0), du(h, 0);
		rep(i, 0, h){
			if(s[i][j] == '#') continue;
			if(i == 0) ud[i] = 1;
			else ud[i] = ud[i - 1] + 1;
		}
		for(int i = h - 1;i >= 0;i--){
			if(s[i][j] == '#') continue;
			if(i == h-1) du[i] = 1;
			else du[i] = du[i + 1] + 1;

			count[i][j] += ud[i] + du[i] - 2;
		}
	}

	for(int i = 0;i < h;i++){
		for(int j = 0;j < w;j++){
			if(s[i][j] == '#') continue;
			int ct = count[i][j];

			ans = (ans + ((powers[ct] - 1) * (powers[k - ct]))%mod)%mod;

		}
	}
	return (int)ans;

}





int DSquares(ll n,ll a,ll b){

	if(a > b) swap(a, b);

	ll ta = ((n - a + 1) * (n - a + 1))%mod;
	ll tb = ((n - b + 1) * (n - b + 1))%mod;
	ll ans = (ta * tb)%mod;
	int ovlen = b + a - 1;

	int len = n - ovlen, wid = n - ovlen;
	
	for(int i = 0;i < ovlen;i++){
		for(int j = 0;j < ovlen;j++){

			ans -= (len - i) * (wid - j);
		}
	}
	return ans;
}

int BFuton(int n,int m,vs s){

	int ans = 0;

	for(int i = 0;i < n;i++){
		for(int j = 0;j < m;j++){
			if(s[i][j] == '#') continue;
			if(j + 1 < m && s[i][j + 1] == '.') ans++;
			if(i + 1 < n && s[i + 1][j] == '.') ans++;
		}
	}
	return ans;

}


int main(){
	int n;
	cin >> n;
	vi nums(n);
	int max_num = 0;
	for(int &a: nums){
		cin >> a;
		max_num = max(max_num, a);
	}
	
	priority_queue<int, vector<int>, greater<int> > pq;
	unordered_set<int> visited;

	int start = 0;
	for(int &a: nums){

		if(visited.count(a) == 0){
			visited.insert(a);
			pq.push(a);
		}

		while(!pq.empty() && pq.top() == start){
			start++, pq.pop();
		}

		cout << start << "\n";
	}
	return 0;
}














