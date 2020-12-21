#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <set>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>
#define vvb vector<vb>

int x[] = {-1, 0, 1, 0};
int y[] = {0, 1, 0, -1};

bool isValidCell(vvb &visited,int i,int j){
	int n = visited.size(), m = visited[0].size();
	if(i < 0 || i >= n || j < 0 || j >= m || visited[i][j]) return false;
	return true;
}

int minimumEffortPath(vvi &heights, vvb &visited,int i = 0,int j = 0){
	int n = heights.size(), m = heights[0].size();
	if(i == n-1 && j == m-1) return 0;
	visited[i][j] = true;
	int ans = INT_MAX;
	for(int k=0;k<4;k++){
		if(isValidCell(visited, i + x[k],j + y[k])){
			int a1 = max(abs(heights[i][j] - heights[i + x[k]][j + y[k]]), 
				minimumEffortPath(heights, visited, i + x[k],j + y[k]));
			ans = min(ans, a1);
		}
	}
	visited[i][j] = false;
	return ans;
}


int minimumEffortPath(vvi &heights){
	priority_queue<vi, vector<vi>, greater<vi> > pq;
	int i = 0, j = 0, cost = 0, n = heights.size(), m = heights[0].size();

	vvi MinHeights(n, vi(m, INT_MAX));
	MinHeights[i][j] = cost;

	pq.push({cost, i, j});
	while(!pq.empty()){
		vi curr = pq.top(); pq.pop();
		cost = curr[0], i = curr[1], j = curr[2];
		if(i == n-1 && j == m-1) return cost;
		for(int k = 0;k < 4;k++){
			int new_i = i + x[k], new_j = j + y[k];
			if(new_i < 0 || new_j < 0 || new_i >= n || new_j >= m) continue;
			int currcost = max(cost, abs(heights[i][j] - heights[new_i][new_j]));
			if(MinHeights[new_i][new_j] > currcost){
				pq.push({currcost, new_i,new_j});
				MinHeights[new_i][new_j] = currcost;
			}
			
		}
	}
	return MinHeights[n-1][m-1];
}

//	Using Sets Instead of Priority Queue
int minimumEffortPath3(vvi &heights){
	int n = heights.size(), m = heights[0].size(), i = 0, j = 0, cost = 0;

	vvi dist(n, vi(m, INT_MAX));
	dist[i][j] = cost;

	set<pair<int, pair<int,int> > > st;
	st.insert({cost, {i, j}});

	while(st.size() > 0){
		pair<int,pair<int,int> > curr = *(st.begin()); st.erase(st.begin());
		cost = curr.first, i = curr.second.first, j = curr.second.second;

		for(int k = 0;k < 4;k++){
			int new_i = i + x[k], new_j = j + y[k];
			if(new_i < 0 || new_j < 0 || new_i >= n || new_j >= m) continue;
			int currcost = max(cost, abs(heights[i][j] - heights[new_i][new_j]));
			if(dist[new_i][new_j] > currcost){

				//	This is what differentiating, It is going to decrease the Search Space
				if(dist[new_i][new_j] != INT_MAX){
					st.erase(st.find({dist[new_i][new_j], {new_i, new_j}}));
				}
				dist[new_i][new_j] = currcost;
				st.insert({currcost, {new_i, new_j}});
			}
		}
	}

	return dist[n-1][m-1];
}




//	Binary Search 
//	Here i need to check whether there is a single path where maxdiff bet consecutive heights
//		diff is <= maxi.
void dfs(vvi &heights, vvb &visited,int i,int j,int maxi){

	visited[i][j] = true;
	for(int k = 0;k < 4;k++){
		int new_i = i + x[k], new_j = j + y[k];
		if(isValidCell(visited, new_i, new_j) && abs(heights[i][j] - heights[new_i][new_j]) <= maxi){
			dfs(heights, visited, new_i, new_j, maxi);
		}
	}
}

int minimumEffortPath2(vvi &heights){
	int l = 0, r = 1e6;
	int n = heights.size(), m = heights[0].size();
	while(l < r){
		int mid = (l + r)/2;
		vvb visited(n, vb(m, false));
		dfs(heights, visited, 0, 0, mid);
		if(visited[n-1][m-1]) r = mid;
		else l = mid + 1;
	}
	return l;
}


int main(){

	return 0;
}


