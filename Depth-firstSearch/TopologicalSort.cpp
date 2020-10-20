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

bool canFinish(int numCourese,vvi &prerequisites){
	return true;
}

void dfs(vvi &adj,vb &visited, int idx,stack<int> &s){

	visited[idx] = true;
	for(int &next: adj[idx]){
		if(!visited[next]) dfs(adj,visited, next, s);
	}
	s.push(idx);
}

bool detectCycleHelper(vvi &adj,int idx,vi &visited){

	if(visited[idx] == 1) return true;
	if(visited[idx] == 2) return false;

	visited[idx] = 1;
	for(int &next: adj[idx])
	{
		if(detectCycleHelper(adj, next, visited)) return true;
	}
	visited[idx] = 2;

	return false;
}

bool detectCycle(vvi &adj){
	int n = adj.size();
	vi visited(n, 0);
	for(int i = 0;i < n;i++){
		if(!visited[i] && detectCycleHelper(adj, i, visited)) return true;
	}

	return false;
}

//	Assumed given Graph is Acyclic
vi topoSort(vvi &adj){
	int n = adj.size();
	vi ans;
	if(detectCycle(adj)) return ans;

	stack<int> s;
	vb visited(n, false);
	for(int i = 0;i < n;i++){
		if(!visited[i]) dfs(adj,visited, i, s);
	}
	while(!s.empty()){
		ans.push_back(s.top());
		s.pop();
	}
	return ans;
}




void dfsHelper(queue<int> &q, vvi &out_edges,vi &in_deg,vi &ans){

	int idx = q.top(); q.pop();
	ans.push_back(idx);

	for(int &next: out_edges[idx]){
		in_deg[next] -= 1;
		if(in_deg[next] == 0) q.push(next);
		dfsHelper(q, out_edges,in_deg, next);
	}
}

vi bfs(queue<int> q, vvi &out_edges, vi &in_deg)
{
	int n = in_deg.size();
	vi ans;
	while(!q.empty()){
		int node = q.front(); q.pop();
		ans.push_back(node);
		for(int &next: out_edges[node]){
			in_deg[next] -= 1;
			if(in_deg[next] < 0) return vi();
			if(in_deg[next] == 0) q.push(next);
		}
	}
	return ans.size() == n?ans:vi();
}

vi topoSort2(vvi &adj){
	queue<int> q;
	int n = adj.size();
	vi in_deg(n, 0);
	vb visited(n, false);
	for(vi &a: adj){
		for(int &b: a) in_deg[b] += 1;
	}
	rep(i, 0, n) if(in_deg[i] == 0) q.push(i);
	return bfs(q, adj, in_deg);
}


void dfsHelper3(vvi &adj,int idx,stack<int> &s, vb &visited){

	visited[idx] = true;
	for(int &next: adj[idx]){
		if(!visited[next]) dfsHelper3(adj, next, s, visited);
	}
	s.push(idx);
}

vi topoSort3(vvi &adj){
	int n = adj.size();
	stack<int> s;
	vb visited(n, false);
	for(int i = 0;i <n;i++){
		if(!visited[i]){
			dfsHelper3(adj, i, stack, visited);
		}
	}
	vi ans;
	while(!s.empty()){
		ans.push_back(s.top());
		s.pop();
	}
	return ans;
}



int main(){

	return 0;
}









