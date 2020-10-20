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

int x[] = {-1, 0, 1, 0};
int y[] = {0, 1, 0, -1};


bool Cycleshelper(vvc &grid, vvi &visited,int i,int j, char color, int len = 1)
{
	int n = grid.size(), m = grid[0].size();
	if(i < 0 || j < 0 || i >= n || j >= m || grid[i][j] != color) return false;

	if(visited[i][j] != 0){
		return (len - visited[i][j]) >= 4;
	}
	visited[i][j] = len;
	rep(k, 0, 4){
		if(Cycleshelper(grid, visited, i + x[k], j + y[k], color, len + 1)) return true;
	}

	return false;
}

bool containsCycle(vvc &grid){
	int n = grid.size();
	if(n == 0) return 0;
	int m = grid[0].size();
	vvi visited(n, vi(m, 0));
	rep(i,0,n){
		rep(j,0,m){
			if(visited[i][j] != 0) continue;
			if(Cycleshelper(grid, visited, i, j, grid[i][j])) return true;
		}
	}
	return false;
}

bool helper(vb &visited,int idx, vi &nums)
{
	visited[idx] = true;
	rep(i,0,4){
		if(visited[i]) continue;

	}
}

vector<double> compute(double x, double y){
	return {x + y, x - y, y - x, x*y, x/y, y/x};
}
double esp = 0.00001;
bool solve(vector<double> &nums,int n)
{
	if(n == 1) return abs(nums[0] - 24) < esp;
	for(int i = 0;i < n;i++){
		for(int j = i + 1;j < n;j++){
			double x = nums[i], y = nums[j];
			nums[j] = nums[n - 1];
			for(double d: compute(x,y))
			{
				nums[i] = d;
				if(solve(nums, n - 1)) return true;
			}
			nums[i] = x, nums[j] = y;
		}
	}
	return false;
}

bool judgePoint24(vi &nums){
	vector<double> nu(nums.begin(), nums.end());
	int n = nums.size();
	return solve(nu, n);
}


int main(){
	int n;
	cin >> n;
	vvc grid(n, vc(n));
	for(vc &a: grid) for(char &b: a) cin >> b;
	cout << containsCycle(grid) << "\n";
	return 0;
}



