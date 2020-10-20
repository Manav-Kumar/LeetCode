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

int x[4] = {-1, 0, 1, 0};
int y[4] = {0, 1, 0, -1};


void dfs(vvi &grid, vvb &visited,int i,int j){
	int n = grid.size(), m = grid[0].size();
	if(i < 0 || j < 0 || i >= n || j >= m || grid[i][j] == 0 || visited[i][j]) return;
	visited[i][j] = true;
	for(int k=0;k<4;k++){
		dfs(grid, visited, i + x[k], j + y[k]);
	}
}

bool isDisconnect(vvi &grid){
	int n = grid.size(), m = grid[0].size(), count = 0;
	vvb visited(n, vb(m, false));
	rep(i, 0, n){
		rep(j, 0, m){
			if(grid[i][j] && !visited[i][j]){
				dfs(grid, visited, i, j);
				count++;
			}
		}
	}

	return count != 1;
}

int minDays(vvi &grid){
	int n = grid.size(), m = grid[0].size();
	if(isDisconnect(grid)) return 0;
	rep(i, 0, n){
		rep(j, 0, m){
			if(grid[i][j]){
				grid[i][j] = 0;
				if(isDisconnect(grid)) return 1;
				grid[i][j] = 1;
			}
		}
	}

	return 2;
}


//	It is like finding the Articulation Points of a graph
void ArticulationHelper(int &ans,int &count, vvi &adj, vb &visited, vi &disc, vi &low,int &timer, int node,int parent = -1){

	visited[node] = true, disc[node] = timer, low[node] = timer++, count++;
	int countChild = 0;
	bool check = false;
	
	for(int &next: adj[node]){
		if(next == parent) continue;
		if(!visited[next]){
			countChild++;
			ArticulationHelper(ans, count, adj, visited, disc, low, timer, next, node);
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

	if(check) ans++;
	else if (parent == -1 && countChild >= 2){//	Root Node
		ans++;
	}
}

bool ValidEdge(vvi &grid, int i,int j){
	int n = grid.size(), m = grid[0].size();
	if(i < 0 || j < 0 || i >= n || j >= m || grid[i][j] == 0) return false;
	return true;
}

int minDays2(vvi &grid){
	int n = grid.size(), m = grid[0].size();

	vvi adj(n*m, vi());
	rep(i, 0, n){
		rep(j, 0, m){
			if(grid[i][j] == 0) continue;
			for(int k = 0;k < 4;k++){
				int newi = i + x[k],newj = j + y[k];
				if(ValidEdge(grid, newi, newj)){
					adj[i*m + j].push_back(newi*m + newj);
				}
			}
		}
	}
	
	vb visited(n*m, false);
	vi disc(n*m, -1), low(n*m, -1);

	bool check = true;
	int ans = 0, count = 0, timer = 1;

	rep(i, 0, n){
		rep(j, 0, m){
			if(grid[i][j] && !visited[i*m + j]){
				if(check){
					check = false;
					ArticulationHelper(ans, count, adj, visited, disc, low, timer, i*m + j);
				}
				else return 0;
			}
			
		}
	}
	
	if(count <= 2) return count;
	return ans == 0?2:1;
}




int main(){
	int n, m;
	cin >> n >> m;
	vvi grid(n, vi(m));
	for(vi &a: grid) for(int &b: a) cin >> b;
	cout << minDays2(grid) << "\n";
	return 0;
}



