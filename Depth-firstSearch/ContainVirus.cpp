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

int x[] = {-1, 0, 1, 0};
int y[] = {0, 1, 0, -1};

void dfs(vvi &grid,vvb &visited, int i,int j,int &peri, set<pair<int,int> > &infectedCells){
	int n = grid.size(), m = grid[0].size();
	if(i < 0 || j < 0 || i >= n || j >= m || visited[i][j] || grid[i][j] == 2) return;

	if(grid[i][j] == 0){
		peri += 1;
		infectedCells.insert(pair<int,int> (i,j));
		return;
	}

	visited[i][j] = true;
	for(int k = 0;k < 4;k++) dfs(grid, visited, i + x[k], j + y[k], peri, infectedCells);

	return;
}


void setWalls(vvi &grid,int i,int j, vvb &visited){
	int n = grid.size(), m = grid[0].size();
	if(i < 0 || j < 0 || i >= n || j >= m || grid[i][j] != 1 || visited[i][j]) return;
	visited[i][j] = true;
	grid[i][j] = 2;
	for(int k = 0;k < 4;k++) setWalls(grid, i + x[k], j + y[k], visited);

	return;
}

void AffectAreas(vvi &grid,int i,int j,vvb &visited){
	int n = grid.size(), m = grid[0].size();
	if(i < 0 || j < 0 || i >= n || j >= m || visited[i][j] || grid[i][j] == 2) return;
	visited[i][j] = true;
	if(grid[i][j] == 0) {grid[i][j] = 1; return;}
	for(int k = 0;k < 4;k++) AffectAreas(grid, i + x[k], j + y[k], visited);

	return;
}

int containVirus(vvi &grid){

	int n = grid.size(), m = grid[0].size();
	vpii regions;
	pair<int,int> largestReg(-1, -1);
	int largestPer = 0, cellsEffected = 0;
	vvb visited(n, vb(m, false));
	rep(i, 0, n){
		rep(j, 0, m){
			if(visited[i][j] || grid[i][j] != 1) continue;
			int peri = 0;
			set<pair<int,int> > infectedCells;
			dfs(grid, visited, i, j, peri, infectedCells);
			if(infectedCells.size() > cellsEffected){
				cellsEffected = infectedCells.size();
				largestPer = peri;
				largestReg = pair<int,int> (i, j);
			}
			regions.push_back(pair<int,int> (i, j));
		}
	}

	if(largestPer == 0){
		//Means no regions is affected
		return 0;
	}

	visited.clear(), visited.resize(n, vb(m, false));
	setWalls(grid, largestReg.first, largestReg.second, visited);

	//	Increase the walls of the regions
	for(pair<int,int> &a: regions){
		if(a == largestReg) continue;
		AffectAreas(grid, a.first, a.second, visited);
	}
	return containVirus(grid) + largestPer;
}


int main(){
	int n, m;
	cin >> n >> m;
	vvi grid(n, vi(m));
	rep(i, 0, n) rep(j, 0, m) cin >> grid[i][j];	
	cout << containVirus(grid) << "\n\n";
	rep(i, 0, n){
		rep(j, 0, m) cout << grid[i][j] << " ";
		cout << "\n";
	}

	return 0;
}

