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
#define vvl vector<vl>
#define vvll vector<vll>
#define vvb vector<vector<bool> >
#define vvvb vector<vvb>

class comparator{
public:

	bool operator()(const pair<int,int> &a,const pair<int,int> &b){
		return a.first < b.first;
	}
};

vector<int> maxSlidingWindow(vector<int>& nums,int k)
{
	vector<int> ans;
	priority_queue<pair<int,int>, vector<pair<int,int> >, comparator> q;
	int i=0,n = nums.size();
	for(;i<k&&i<n;i++) q.push(pair<int,int> (nums[i], i));
	ans.push_back(q.top().first);
	while(i < n)
	{
		q.push(pair<int,int> (nums[i], i));
		pair<int,int> top = q.top();
		while(top.second <= (i - k)){
			q.pop();
			top = q.top();
		}
		ans.push_back(top.first);
		i++;
	}
	return ans;
}


//	Shortest Path To Get All Keys
int xDir[] = {-1, 0, 1, 0};
int yDir[] = {0, 1, 0, -1};

int helper(vector<string> &grid,vvvb &visited,int i,int j,int allmask,int mask){
	
	if(mask == allmask) return 0;
	int n = grid.size(), m = grid[0].size();
	if(i < 0 || j < 0 || i >= n || j >= m || visited[i][j][mask] || grid[i][j] == '#') return INT_MAX;

	visited[i][j][mask] = true;
	if(grid[i][j] >= 'A' && grid[i][j] <= 'F'){
		if((mask&(1<<(grid[i][j] - 'A'))) == 0) return INT_MAX;
	}
	if(grid[i][j] >= 'a' && grid[i][j] <= 'f'){
		mask |= 1<<(grid[i][j] - 'a');
	}
	int ans = INT_MAX;
	for(int k=0;k<4;k++){
		int temp = helper(grid, visited, i + xDir[k], j + yDir[k], allmask, mask);
		if(temp != INT_MAX) temp += 1;
		ans = min(ans, temp);
	}
	return ans;
}

//	Here DFS approach is not helpful SO AVOID IT BELOW CODE WOULD COMPILED BUT NOT AT ALL RIGHT
//	ITS JUST FOR REFERENCE WHERE DFS IS NOT HELPFUL, IT WON'T PASS TEST CASES OF SOLUTION
//		HERE PROBLEM IS WE NOT ONLY HAD TO REACH A PARTICULAR STATE BUT ALSO IN MINIMUM NUMBER
//		OF STEPS, DFS WILL MAKE A PARTICULAR STATE TO BE TRUE WON'T BY NOT CONSIDERING THE HOW MANY
//		STEPS DOES IT TOOK, WHICH IS VERY BAD BECAUSE IT MAY HAPPEN AT A PARTICULAR STATE WE MAY REACH
//		MUCH BEFORE THAN WHEN IT HAS ACTUALLY BEEN MADE TRUE AND ITS CORRESPONDING ANS WILL CHANGE

//	AVOID BELOW WRITTEN SOLUTION

int ShortestPathAllKeys(vector<string>& grid)
{
	int n = grid.size(), m = grid[0].size(),x,y, allmask = 0;
	
	rep(i,0,n) 
	{
		rep(j,0,m) {
			if(grid[i][j] == '@'){
				x = i, y = j;
			}
			else if(grid[i][j] >= 'a' && grid[i][j] <= 'f') allmask |= 1<<(grid[i][j] - 'a');
		}
	}
	vvvb visited(n, vvb(m, vb(allmask + 1, false)));

	int ans = helper(grid, visited, x, y, allmask, 0);
	if(ans == INT_MAX) return -1;
	return ans;
}

// CORRECT BFS WRITTEN APPROACH, using dijkastra we can implment it via dfs, otherwise use SIMPLE BFS

int ShortestPathAllKeys2(vector<string> grid)
{
	int n = grid.size(), m = grid[0].size(), allmask = 0;
	vector<int> temp;
	rep(i,0,n){
		rep(j,0,m){
			if(grid[i][j] == '@') temp = {i,j};
			else if(grid[i][j] >= 'a' && grid[i][j] <= 'f'){
				allmask |= (1<<(grid[i][j] - 'a'));
			}
		}
	}

	temp.push_back(0);
	temp.push_back(0);
	queue<vector<int> > q;
	vector<vector<vector<int> > > grey(n, vector<vector<int> >(m, vector<int> (allmask+1, 0)));
	grey[temp[0]][temp[1]][temp[2]] = 1;
	q.push(temp);
	while(!q.empty())
	{
		temp = q.front();
		q.pop();
		int i = temp[0], j = temp[1], mask = temp[2], d = temp[3];
		if(mask == allmask) return d;

		for(int k=0;k<4;k++){
			int x = i + xDir[k], y = j + yDir[k];
			if(x>=0&&x<n&&y>=0&&y<m)
			{
				if(grid[x][y] >= 'a' && grid[i][j] <= 'f' && (mask&(1<<(grid[x][y] - 'a'))) == 0){
					q.push({x,y, mask|(1<<(grid[x][y] - 'a')), d+1 });
					grey[x][y][(1<<(grid[x][y] - 'a'))] = 1;
				}
				else if(grey[x][y][mask] == 0){

					if(grid[x][y] >= 'A' && grid[x][y] <= 'F' && (mask&(1<<(grid[x][y] - 'A'))) != 0){
						q.push({x, y, mask, d+1});
						grey[x][y][mask] = 1;
					}
					else if(grid[x][y] == '.' || grid[x][y] == '@' || (grid[x][y] >= 'a' && grid[x][y] <= 'f')){
						q.push({x, y, mask, d+1});
						grey[x][y][mask] = 1;
					}
				}
			}
		}
	}
	return -1;
}



int main()
{
	int n;
	cin >> n;
	vector<string> grid(n);
	for(string &s: grid) cin >> s;
	cout << ShortestPathAllKeys(grid) << "\n";
	return 0;
}
