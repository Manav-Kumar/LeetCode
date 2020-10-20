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
#define vd vector<double>
#define vvd vector<vd>
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>

int x[4] = {-1, 0, 1, 0};
int y[4] = {0, 1, 0, -1};

int helper(vvi &grid,vvb &visited, int i,int j){

	int n = grid.size();

	if(i < 0 || j < 0 || i >= n || j >= n || visited[i][j]) return INT_MAX;
	if(grid[i][j] == 1) return 0;
	visited[i][j] = true;

	int ans = INT_MAX;
	for(int k = 0;k < 4;k++){
		int a1 = helper(grid, visited, i + x[k], j + y[k]);
		if(a1 != INT_MAX) a1 += 1;
		ans = min(ans, a1);
	}
	return ans;
}

int maxDistance(vvi &grid){
	int n = grid.size(), ans = -1;
	vvi count(n, vi(n, -2));
	rep(i, 0, n){
		rep(j, 0, n){
			if(grid[i][j] == 0){
				vvb visited(n, vb(n, false));
				ans = max(ans, helper(grid, visited, i, j));
			}
		}
	}
	return ans == INT_MAX?-1:ans;
}

int maxDistance2(vvi &grid){
	int n = grid.size(), ans = -1;


	rep(i, 0, n){
		rep(j, 0, n){
			if(grid[i][j] == 0){
				int temp = INT_MAX;
				rep(x, 0, n){
					rep(y, 0, n){
						if(grid[x][y] == 1) temp = min(temp, abs(x - i) + abs(y - j));
					}
				}
				ans = max(ans, temp);
			}
		}
	}
	
	return ans == INT_MAX?-1: ans;
}


int helper3(vvi &grid,int si,int sj){
	queue<int> pq;
	int n = grid.size(), count = 0;
	unordered_set<int> visited;
	pq.push(si*n + sj);
	visited.insert(si*n + sj);
	while(!pq.empty()){
		int sz = pq.size();
		while(sz--){
			int node = pq.front(); pq.pop();
			int r = node/n , c = node%n;
			for(int k = 0;k < 4;k++){
				int i = r + x[k], j = c + y[k];
				if(i < 0 || j < 0 || i >= n || j >= n || visited.count(i*n + j) > 0) continue;
				if(grid[i][j] == 1) return count + 1;
				visited.insert(i*n + j), pq.push(i*n + j);
			}
		}
		count++;
	}

	return -1;
}

int maxDistance3(vvi &grid){
	int n = grid.size(), ans = -1;
	rep(i, 0, n){
		rep(j, 0, n){
			if(grid[i][j] == 0) ans = max(ans, helper3(grid, i, j));
		}
	}
	return ans;
}


int maxDistance4(vvi &grid){
	int n = grid.size(), ans = -1;
	queue<pair<int,int> > Q;
	vvb visited(n, vb(n, false));
	rep(i, 0, n){
		rep(j, 0, n){
			if(grid[i][j]){
				Q.push({i, j});
				visited[i][j] = true;
			}
		}
	}

	if(Q.size() == 0 || Q.size() == n*n) return -1;
	int l = -1;
	while(!Q.empty()){
		l++;
		int sz = Q.size();
		while(sz--){
			int tx = Q.front().first, ty = Q.front().second;
			Q.pop();
			for(int k = 0;k < 4;k++){
				int i = tx + x[k], j = ty + y[k];
				if(i < 0 || j < 0 || i >= n || j >= n || visited[i][j]) continue;
				visited[i][j] = true, Q.push({i, j});
			}
		}
	}

	return l;
}



int main(){
	int n;
	cin >> n;
	vvi grid(n, vi(n));
	for(vi &a: grid) for(int &b: a) cin >> b;
	cout << maxDistance3(grid) << "\n";
	return 0;
}



