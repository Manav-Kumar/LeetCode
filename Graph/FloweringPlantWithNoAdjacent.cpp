#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>

vi ans;

bool dfs(vvi &adj, int start, vb &visited, int count = 0){

	visited[start] = true;
	vb avaialble(4, true);
	for(int &next: adj[start]){
		if(visited[next]) avaialble[ans[next]] = false;
	}

	for(int i=0;i<4;i++){
		if(avaialble[i]){
			avaialble[i] = false, ans[start] = i;
			if(count == visited.size() - 1) return true;
			bool t = true;
			for(int &next: adj[start]){
				if(!visited[next]) t = t && dfs(adj, next, visited, count + 1);

				if(!t) break;
			}

			if(t) return true;
		}
	}
	visited[start] = false;
	return false;
}



vector<int> gardenNoAdj(int n, vector<vector<int> > &paths){
	ans.clear(), ans.resize(n, -1);
	vvi adj(n, vector<int> ());
	for(vi &a: paths){
		adj[a[0] - 1].push_back(a[1] - 1);
		adj[a[1] - 1].push_back(a[0] - 1);
	}
	vb visited(n, false), avaialble(4, true);
	bool t = true;
	for(int i=0;i<n;i++){
		if(!visited[i]) dfs(adj, i, visited);
	}

	return ans;
}

//	Greedy Approach
vi gardenNoAdj2(int n, vvi &paths){
	vvi adj(n, vector<int> ());
	for(vi &a: paths){
		adj[a[0] - 1].push_back(a[1] - 1);
		adj[a[1] - 1].push_back(a[0] - 1);
	}
	vector<int> ans(n,0);
	for(int i=0;i<n;i++){
		if(adj[i].size() == 0) ans[i] = 1;
		else{
			vb avaialble(5, true);
			for(int &next: adj[i]){
				if(ans[next] != 0) avaialble[ans[next]] = false;
			}

			for(int j=1;j<=4;j++){
				if(avaialble[j]){
					ans[i] = j; break;
				}
			}
		}
	}

	return ans;
}

int main(){
	int n, m;
	cin >> n >> m;
	vvi paths(m, vi(2));
	for(vi &a: paths) cin >> a[0] >> a[1];
	vector<int> ans = gardenNoAdj(n, paths);	
	for(int a: ans) cout << a+1 << " ";
	return 0;
}



