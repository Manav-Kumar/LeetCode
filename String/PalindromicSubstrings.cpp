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
#include <list>
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
#define vvvi vector<vvi>
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>

bool isPanlindrom(string &s, int st,int en){
	while(st <= en){
		if(s[st++] != s[en--]) return false;
	}
	return true;
}
void helper(string &s, int st,int en, vvb &dp,int &count, vvb &check){
	if(dp[st][en]) return;
	if(st == en){
		count++, dp[st][en] = true;
		return ;
	}
	
	if(check[st][en]) count++;
	for(int i = st + 1;i <= en;i++){
		helper(s, st, i - 1, dp, count, check);
		helper(s, i, en, dp, count, check);
	}
	dp[st][en] = true;
}


int BitnoicSeq(vi &a){
	int n = a.size();
	vi incre(n,0), decre(n, 0);
	incre[0] = 1;
	rep(i, 1, n){
		if(a[i] > a[i - 1]) incre[i] = incre[i - 1] + 1;
		else incre[i] = 1;
	}
	decre[n - 1] = 1;
	for(int i = n - 2;i >= 0;i--){
		if(a[i] > a[i + 1]) decre[i] = decre[i + 1] + 1;
		else decre[i] = 1;
	}
	int ans = 0;
	rep(i, 0, n){
		ans = max(ans, incre[i] + decre[i]);
	}
	return ans;
}

int BitnoicSeqDecLeft(vi &a,vvi &dp, int idx,int last, bool &ck){

	if(idx < 0) return 0;

	if(dp[idx][last] != -1) return dp[idx][last];

	int a1 = 0, a2 = 0, s = 0;
	if(!ck) ck = true, s = 1;

	if(a[idx] < last) a1 = BitnoicSeqDecLeft(a, dp, idx - 1, a[idx], ck) + 1;
	a2 = BitnoicSeqDecLeft(a, dp, idx - 1, last, ck);

	if(s == 1){
		if(a1 > a2) ck = true;
		else ck = false;
	}

	dp[idx][last] = max(a1, a2);
	return dp[idx][last];
}

int BitnoicSeqDecRight(vi &a, vvi &dp, int idx,int last, bool &ck){
	if(idx >= a.size()) return 0;

	if(dp[idx][last] != -1) return dp[idx][last];

	int a1 = 0, a2 = 0, s = 0;
	if(!ck) ck = true, s = 1;

	if(a[idx] < last) a1 = BitnoicSeqDecRight(a, dp, idx + 1, a[idx], ck) + 1;
	a2 = BitnoicSeqDecRight(a, dp, idx + 1, last, ck);

	if(s == 1){
		if(a1 > a2) ck = true;
		else ck = false;
	}
	dp[idx][last] = max(a1, a2);
	return dp[idx][last];
}

int main(){
	int t, n;
	vi a;
	cin >> t;
	while(t--){
		cin >> n;
		a.clear(), a.resize(n);
		for(int &b: a) cin >> b;
		int ans = 0;
		rep(i, 0, n){
			vvi dp1(n, vi(202, -1)), dp2(n, vi(202, -1));
			bool ck1 = false, ck2 = false;
			int a2 = BitnoicSeqDecRight(a, dp2, i, 201, ck1);
			int a1 = BitnoicSeqDecLeft(a, dp1, i, 201, ck2);
			ans = max(ans, a1 + a2 + ((ck1 && ck2)?-1:0));
		}

		cout << ans << "\n";

	}
	return 0;
}

