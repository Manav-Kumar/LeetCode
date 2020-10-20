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

bool PreReq(vvi &adj,int st,int en,int start, vvi &isPre){

	int &check = isPre[st][en];
	if(st == en) return check = 1;
	isPre[start][st] = 1;
	if(check != -1) return check;
	check = false;
	for(int &next: adj[st]){
		check = PreReq(adj, next, en, start, isPre);
		if(check) return true;
	}

	return check;
}

vb checkIfPrerequisite(int n, vvi &prerequisites, vvi &queries){
	vvi adj(n);
	for(vi &a: prerequisites){
		adj[a[0]].push_back(a[1]);
	}
	vvi isPre(n, vi(n, -1));
	vb ans;
	for(vi &q: queries){
		ans.push_back(PreReq(adj, q[0], q[1], q[0], isPre));
	}
	return ans;
}

vb checkIfPrerequisite2(int n,vvi &prerequisites,vvi &queries){

	vvi dp(n, vi(n, 0));
	for(vi &a: prerequisites){
		dp[a[0]][a[1]] = 1; 
	}
	rep(k, 0, n){
		rep(i, 0, n){
			rep(j, 0, n){
				dp[i][j] = max(dp[i][j], dp[i][k] * dp[k][j]);
			}
		}
	}
	vb ans;
	for(vi &q: queries){
		ans.push_back(dp[q[0]][q[1]]);
	}
	return ans;
}



//	Miniumum Height Trees
int maxHeight(vvi &adj, vi &heights,int idx = 0,int parent = -1){

	int ans = 1;
	for(int &next: adj[idx]){
		if(next != parent) ans = max(ans, maxHeight(adj, heights, next, idx) + 1);
	}
	heights[idx] = ans;
	return ans;
}


void helper(vvi &adj,vi &heights,int &ans, int idx = 0,int parent = -1,int ht = 0){

	heights[idx] = max(heights[idx], ht + 1);
	ans = min(ans, heights[idx]);
	int firHt = 0, SecHt = 0, fi = -1, si = -1;
	for(int &next: adj[idx]){
		if(parent != next){
			if(firHt < heights[next]){
				SecHt = firHt, firHt = heights[next];
				si = fi, fi = next;
			}
			else if(SecHt < heights[next]) SecHt = heights[next], si = next;
		}
	}
	for(int &next: adj[idx]){
		if(parent == next) continue;
		int v = fi != next && fi != -1?firHt: (si != next && si != -1?SecHt:0);
		helper(adj, heights, ans, next, idx, max(ht + 1,v + 1));
	}

}


vi findMinHeightTrees(int n, vvi &edges){
	vi heights(n, 0);
	vvi adj(n);
	for(vi &a: edges){
		adj[a[0]].push_back(a[1]);
		adj[a[1]].push_back(a[0]);
	}
	int ht = maxHeight(adj, heights);
	int ans = INT_MAX;
	helper(adj, heights, ans);
	vi finalAns;
	for(int i = 0;i < n;i++){
		if(heights[i] == ans) finalAns.push_back(i);
	}
	return finalAns;
}


int main(){
	int n, m;
	cin >> n >> m;
	vvi edges(m, vi(2));
	for(vi &a: edges) cin >> a[0] >> a[1];
	vi ans = findMinHeightTrees(n, edges);
	for(int &a: ans) cout << a << " ";
	cout << "\n";
	return 0;
}





