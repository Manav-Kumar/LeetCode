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
#define vs vector<string>

int x[] = {-1, 0, 1, 0};
int y[] = {0, 1, 0, -1};

int helperLonPath(vvi &matrix, vvi &visited, int i,int j,int prev = -1)
{
	int n = matrix.size(), m = matrix[0].size();
	if(i < 0 || j < 0 || i >= n || j >= m || matrix[i][j] <= prev) return 0;
	int &ans = visited[i][j];
	if(ans != -1) return ans;
	ans = 1;
	int value = matrix[i][j];
	for(int k = 0;k < 4;k++){
		ans = max(ans, helperLonPath(matrix, visited,i + x[k], j + y[k], value) + 1);
	}

	visited[i][j] = ans;
	return ans;
}

int longestIncreasingPath(vvi &matrix){
	int n = matrix.size();
	if(n == 0) return 0;
	int m = matrix[0].size() , ans = 0;
	vvi visited(n, vi(m, false));
	rep(i,0, n){
		rep(j, 0, m) ans = max(ans, helperLonPath(matrix, visited, i, j));
	}

	return ans;
}


//	Making a LargeIsland
void helper(vvi &grid,vvb &visited, int i,int j,int &count, vector<pair<int,int> > &zeros){

	int n = grid.size(), m = grid[0].size();
	if(i < 0 || j < 0 || i >= n || j >= m || visited[i][j]) return ;
	if(grid[i][j] == 0){
		if(find(zeros.begin(), zeros.end(), pair<int,int> (i,j)) == zeros.end()) zeros.push_back(pair<int,int> (i,j));
		return;
	}
	visited[i][j] = true;
	count++;
	rep(k, 0, 4){
		helper(grid, visited,i + x[k], j + y[k], count, zeros);
	}

}

int LargeIsland(vvi &grid)
{
	int n = grid.size(), m = grid[0].size(), ans = 0;
	vvb visited(n, vb(m, false));
	vvi sum(n, vi(m, 0));
	rep(i,0,n){
		rep(j,0,m){
			if(visited[i][j] || grid[i][j] == 0) continue;
			vector<pair<int,int> > zeros;
			int count = 0;
			helper(grid, visited, i, j, count, zeros);
			ans = max(ans, count);
			for(pair<int,int> &a: zeros){
				sum[a.first][a.second] += count;
			}
		}
	}
	rep(i,0,n){
		rep(j,0,m) if(grid[i][j] == 0) ans = max(ans, sum[i][j] + 1);
	}

	return ans;
}


int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	vvi grid(n, vi(n, -1));
	for(vi &a: grid) for(int &b: a) cin >> b;
	cout << LargeIsland(grid) << "\n";
	return 0;
}