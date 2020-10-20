#include <iostream>
#include <vector>
#include <queue>
#include <map>
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
#define vvi vector<vector<int> >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>


vi parent;
vb visited;
vi low;
vi disc;
vvi bridges;
vvi adj;

void dfs(int idx,int &time, int parent = -1){

	disc[idx] = low[idx] = ++time;
	visited[idx] = true;
	for(int &neighbors: adj[idx])
	{
		if(!visited[neighbors]){

			dfs(neighbors, time, idx);

			low[idx] = min(low[idx], low[neighbors]);

			if(low[neighbors] > disc[idx]){
				bridges.push_back({idx, neighbors});
			}
		}
		else if(neighbors != parent) {
			low[idx] = min(low[idx], low[neighbors]);
		}
	}
}


vvi criticalConnections(int n, vvi &connections){
	parent.resize(n, -1);
	low.resize(n, -1);
	disc.resize(n, -1);
	adj.resize(n);
	visited.resize(n, false);

	for(vi &edge: connections){
		adj[edge[0]].push_back(edge[1]);
		adj[edge[1]].push_back(edge[0]);
	}
	int time = 0;
	rep(i, 0, n){
		if(!visited[i]) dfs(i, time);
	}
	return bridges;
}

// void dfs(int idx,int &time)
// {
// 	visited[idx] = true;
// 	low[idx] = disc[idx] = ++time;

// 	for(int &neighbors: adj[idx])
// 	{
// 		if(!visited[neighbors]){

// 			dfs(neighbors, time);
// 			low[idx] = min(low[idx], low[neighbors]);

// 			if(low[neighbors] > disc[idx]){
// 				bridges.push_back({idx, neighbors});
// 			}
// 		}
// 		else if(neighbors != parent){
// 			low[idx] = min(low[idx], low[neighbors]);
// 		}
// 	}
// }

int main(){

	return 0;
}






