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


//	Tarjan's Alg
void tarjanHelper(vvi &ans, vvi &adj, vb &visited, vi &disc, vi &low,int &timer, int node = 0,int parent = -1){

	visited[node] = true, disc[node] = timer, low[node] = timer++;
	for(int &next: adj[node]){
		if(next == parent) continue;
		if(!visited[next]){
			tarjanHelper(ans, adj, visited, disc, low, timer, next, node);
			low[node] = min(low[node], low[next]);
			if(disc[node] < low[next]) ans.push_back({node, next});
		}
		else low[node] = min(low[node], disc[next]);//It's a backedge
	}
}

vvi getBridge(int n, vvi &adj){
	//	Assuming we got the single connected Component and need to find the bridges
	vi disc(n, -1), low(n, -1);
	vb visited(n, false);
	vvi ans;
	int timer = 1;
	tarjanHelper(ans, adj, visited, disc, low, timer);
	return ans;
}


//	Articulation Points
void ArticulationHelper(vi &ans, vvi &adj, vb &visited, vi &disc, vi &low,int &timer, int node = 0,int parent = -1){

	visited[node] = true, disc[node] = timer, low[node] = timer++;
	int countChild = 0;
	bool check = false;
	for(int &next: adj[node]){
		if(next == parent) continue;
		if(!visited[next]){
			countChild++;
			ArticulationHelper(ans, adj, visited, disc, low, timer, next, node);
			low[node] = min(low[node], low[next]);
			if(disc[node] < low[next]) check = true;
		}
		else{
			low[node] = min(low[node], disc[next]);//It's a backedge
		}
	}

	if(countChild == 0){//	Leaf Node
		return;
	}

	if(check) ans.push_back(node);
	else if (parent == -1 && countChild >= 2){//	Root Node
		ans.push_back(node);
	}
}

vi getCutVertices(int n,vvi &adj){
	vi disc(n, -1), low(n, -1);
	vb visited(n, false);
	vi ans;
	int timer = 1;
	ArticulationHelper(ans, adj, visited, disc, low, timer);
	
	return ans;
}

int main(){
	int n, m, t1, t2;
	cin >> n >> m;
	vvi adj(n, vi());
	while(m--){
		cin >> t1 >> t2;
		adj[t1].push_back(t2), adj[t2].push_back(t1);
	}
	vi ans = getCutVertices(n, adj);
	for(int &a: ans) cout << a << " ";
	return 0;
}



