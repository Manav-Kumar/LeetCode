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

//	Directed Graph

bool dfs(vvi &edges,vb &visited, int idx,int node,int &count){

	if(visited[node]) return false;

	visited[node] = true, count++;
	rep(i, 0, edges.size()){
		if(i == idx || edges[i][0] != node) continue;
		bool check = dfs(edges, visited, idx, edges[i][1], count);
		if(!check) return false;
	}
	return true;
}

bool isSafeToRemove(vvi &edges,int idx,int start){
	int n = edges.size(), count = 0;
	vb visited(n + 1, false);
	return dfs(edges, visited, idx, start, count) && count == n;
}


vi detectCycle(vvi &edges){
	//	Every Node has 1 Parent
	int n = edges.size(), node = 1;
	vi parent(n + 1, -1), child(n + 1, -1), indexes(n + 1, -1);
	for(int i = 0;i < edges.size();i++){
		vi a = edges[i];
		parent[a[1]] = a[0], indexes[a[1]] = i;
	}
	vb visited(n + 1, false);
	while(1){
		if(visited[node]){
			int k = parent[node], ans = indexes[node];
			while(k != node){
				ans = max(ans, indexes[k]);
				k = parent[k];
			}
			return edges[ans];
		}
		visited[node] = true, child[parent[node]] = node;
		node = parent[node];
	}
}

vi findRedundantConnection(vvi &edges){
	int n = edges.size(), indegNode = -1, zerdegnode = -1;
	vi parent(n + 1, 0);
	for(vi &a: edges){
		parent[a[1]] += 1;
	}
	bool check = true;
	rep(i,1,n+1){
		if(parent[i] != 1) check = false;
		if(parent[i] == 2) indegNode = i;
		if(parent[i] == 0) zerdegnode = i;
	}
	if(check) return detectCycle(edges);//	Similar To Undirected Graph

	for(int i = n - 1;i >= 0;i--){
		if(edges[i][1] == indegNode){
			if(isSafeToRemove(edges, i, zerdegnode)) return edges[i];
		}
	}
	return vi();
}

bool SameComponent(vi &Component,int &st,int &en){
	while(Component[st] != st) st = Component[st];
	while(Component[en] != en) en = Component[en];
	return st == en;
}

vi findRedundantConnection2(vvi &edges){
	int n = edges.size();
	vi Component(1, 0), mp(n + 1, 0), ans1(2,0), ans2(2,0);

	for(vi &edg: edges){
		int u = edg[0], v = edg[1];
		if(mp[v] > 0){
			ans1 = {mp[v], v};
			ans2 = edg;
		}
		else mp[v] = u;
	}
	rep(i, 1, n + 1) Component.push_back(i);

	for(int i = 0;i < n;i++){

		if(ans2 == edges[i]) continue;

		int st = edges[i][0], en = edges[i][1];

		if(SameComponent(Component, st, en)){
			return ans1[0] == 0?edges[i]:ans1;
		}
		
		Component[en] = st;
	}
	return ans2;
}


int main(){
	int m;
	cin >> m;
	vvi edges(m, vi(2));
	for(vi &a: edges) cin >> a[0] >> a[1];
	vi ans = findRedundantConnection2(edges);
	cout << ans[0] << " " << ans[1] << "\n";
	return 0;
}

