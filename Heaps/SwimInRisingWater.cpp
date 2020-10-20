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
#include <deque>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vl vector<long>
#define vll vector<long long>
#define vc vector<char>
#define vs vector<string>
#define vvc vector<vc>
#define vvi vector<vector<int> >
#define vvvi vector<vvi>
#define vvl vector<vl>
#define vvll vector<vll>
#define vvb vector<vector<bool> >
#define vvvb vector<vvb>

int xDir[] = {-1, 0, 1, 0};
int yDir[] = {0, 1, 0, -1};

bool isValid(int &x,int &y,int &n,vvb &visited){
	if(x < 0 || y < 0 || x >= n || y >= n || visited[x][y]) return false;
	return true;
}

int helper(vvi &grid,vvb &visited,int i = 0,int j = 0,int t = 0)
{
	int n = grid.size();
	if(i == n-1 && j == n-1) return t;
	visited[i][j] = true;
	int ans = INT_MAX;
	for(int k=0;k<4;k++){
		int x = i + xDir[k], y = j + yDir[k];
		if(isValid(x,y,n,visited)){
			int new_t = t >= max(grid[i][j], grid[x][y])?t: max(grid[i][j], grid[x][y]);
			int a1 = helper(grid, visited, x, y, new_t);
			ans = min(ans, a1);
		}
	}
	visited[i][j] = false;
	return ans;
}


bool isValid3(int &x,int &y,int &n){
	if(x < 0 || y < 0 || x >= n || y >= n) return false;
	return true;
}
int helper3(vvi &grid,vvvi &visited,int i = 0,int j = 0,int t = 0)
{
	int n = grid.size();
	if(i == n-1 && j == n-1) return t;
	visited[i][j][t] = 1;
	int ans = INT_MAX;
	for(int k=0;k<4;k++){
		int x = i + xDir[k], y = j + yDir[k];
		if(isValid3(x,y,n)){
			int new_t = t >= max(grid[i][j], grid[x][y])?t: max(grid[i][j], grid[x][y]);
			int a1 = INT_MAX;
			if(visited[x][y][new_t] == 0) a1 = helper3(grid, visited, x, y, new_t);
			ans = min(ans, a1);
		}
	}
	return ans;
}


int swimInWater(vvi& grid)
{
	int n = grid.size();

	vvvi visited2(n, vvi(n, vi(n*n ,0)));
	vvb visited(n, vb(n, false));
	return helper3(grid, visited2);
}


//	BFS
class node{
public:
	int x,y,t;
	node(int x = 0,int y = 0,int t = 0): x(x), y(y), t(t) {}
};

class comparator{
public:
	bool operator()(const node &a, const node &b){
		return a.t > b.t;
	}
};

int swimInWater2(vvi &grid)
{
	int n = grid.size();
	priority_queue<node, vector<node>, comparator> q;
	vvi visited(n, vi(n, 0));
	//Here visited array needed to be only 2D as priority queue would always be first taking out
	//	least time taking node hence we will always be dealing (i,j) which is reached in least time
	//	before other cases where we might take extra time.
	node temp(0, 0, 0);
	q.push(temp);
	while(!q.empty()){
		temp = q.top();
		q.pop();
		int i = temp.x, j = temp.y, t = temp.t;
		if(i == n-1 && j == n-1) return t;
		for(int k=0;k<4;k++){
			int x = i + xDir[k], y = j + yDir[k];
			if(x < 0 || y < 0 || x >= n || y >= n) continue;
			int new_t = t >= max(grid[i][j], grid[x][y])?t: max(grid[i][j], grid[x][y]);
			if(visited[x][y] != 0) continue;
			q.push(node(x, y, new_t));
			visited[x][y] = 1;
		}
	}
	return 0;
}

int main()
{
	int n;
	cin >> n;
	vvi grid(n, vi(n,0));
	for(vi &a: grid) for(int &b: a) cin >> b;
	cout << swimInWater2(grid) << "\n";
	return 0;
}

