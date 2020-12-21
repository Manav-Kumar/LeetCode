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

int findCheapestPrice(vvpii &flights, int src,int dst,int k,vvi &dp){

	if(src == dst) return 0;
	if(k < 0) return INT_MAX;
	if(dp[src][k] != -1) return dp[src][k];
	int ans = INT_MAX;
	for(pair<int,int> &a: flights[src]){
		int p = findCheapestPrice(flights, a.first, dst, k - 1, dp);
		if(p != INT_MAX) ans = min(ans, p + a.second);
	}

	return dp[src][k] = ans;
}

int findCheapestPrice(int n,vvi &flights,int src,int dst,int K){
	vvpii arr(n);
	for(vi &a: flights){
		arr[a[0]].push_back({a[1], a[2]});
	}
	vvi dp(n, vi(K + 1, -1));
	int ans = findCheapestPrice(arr, src, dst, K, dp);
	if(ans ==INT_MAX) return -1;
	return ans;
}

//	BFS
int findCheapestPrice2(int n, vvpii &flights,int src,int dst,int k){
	if(src == dst) return 0;
	queue<pair<int,int> > q;
	q.push({src, 0});
	int ans = INT_MAX;
	while(!q.empty()){
		if(k < 0) break;
		int sz = q.size();
		rep(l, 0, sz){
			int src = q.front().first, cost = q.front().second; q.pop();
			for(pair<int,int> &a: flights[src]){
				if(a.first == dst) ans = min(ans, cost + a.second);
				else if(ans > cost + a.second) q.push({a.first, cost + a.second});
			}
		}
		k--;
	}
	return ans == INT_MAX?-1:ans;
}

//	PriorityQueue
int findCheapestPrice3(int n, vvi &flights, int src,int dst,int k){
	unordered_map<int, vpii> adj;
	for(vi &a: flights){
		adj[a[0]].push_back({a[1], a[2]});
	}
	priority_queue< vi, vector<vi>, greater<vi> > q;
	q.push( { 0, src, k } );
	while(!q.empty()){
		vi t = q.top(); q.pop();
        int cost = t[0], curr = t[1], stop = t[2];
        if(curr == dst) return cost;
        if(stop < 0) continue;

		for(pair<int,int> &a: adj[curr]){
			q.push({cost + a.second, a.first, stop - 1});
		}
	}
	return -1;
}





int main(){
	int n, m, src, dst, k;
	cin >> n >> m;
	vvi flights(m, vi(3));
	for(vi &a: flights) cin >> a[0] >> a[1] >> a[2];
	cin >> src >> dst >> k;
	cout << findCheapestPrice3(n, flights, src, dst, k) << "\n";
	return 0;
}


