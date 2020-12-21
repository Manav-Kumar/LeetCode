#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>

int dire_x[] = {-1, 0, 1, 0};
int dire_y[] = {0, 1, 0, -1};


class Solution{
	int m, n;
	vvb visited;
public:

	bool isValid(int x,int y){
		if(x < 0 || y < 0 || x >= m || y >= n) return false;
		return true;
	}

	int BFS(vvi &forest,vi start,vi end){
		int t = 0;
		for(int i=0;i<m;i++) for(int j=0;j<n;j++) visited[i][j] = false;

		queue<int> q_x, q_y;
		q_x.push(start[0]), q_y.push(start[1]);
		visited[start[0]][start[1]] = true;
		while(!q_x.empty()){
			int l = q_x.size();
			for(int i=0;i<l;i++){
				int x = q_x.front(), y = q_y.front(); q_x.pop(), q_y.pop();

				if(forest[x][y] == forest[end[0]][end[1]]) return t;
				for(int k=0;k<4;k++){
					int new_x = x + dire_x[k], new_y = y + dire_y[k];
					if(isValid(new_x, new_y) && !visited[new_x][new_y] && forest[new_x][new_y] != 0){
						if(forest[new_x][new_y] == forest[end[0]][end[1]]) return t + 1;
						visited[new_x][new_y] = true, q_x.push(new_x), q_y.push(new_y);
					} 
				}
			}
			t++;
		}
		return -1;
	}

	int distanceVectors(vi a, vi b){
		return abs(a[0] - b[0]) + abs(a[1] - b[1]);
	}

	int A_star(vvi &forest, vi start,vi end){

		int t = 0;
		priority_queue<vi, vector<vi>, greater<vi> > pq;

		pq.push({0 + distanceVectors(start, end), start[0], start[1]});

		while(pq.size() > 0){
			int l = pq.size();
			for(int i=0;i<l;i++){
				vi curr = pq.top(); pq.pop();
				int x = curr[1], y = curr[2];

				if(forest[x][y] == forest[end[0]][end[1]]) return t;

				for(int k=0;k<4;k++){
					int new_x = x + dire_x[k], new_y = y + dire_y[k];

					if(isValid(new_x, new_y) && !visited[new_x][new_y] && forest[new_x][new_y] != 0){
						if(forest[new_x][new_y] == forest[end[0]][end[1]]) return t + 1;
						visited[new_x][new_y] = true;
						int dst = distanceVectors(start, {new_x, new_y}) + distanceVectors({new_x, new_y}, end);
						pq.push({dst, new_x, new_y});
					}
				}
			}
			t++;
		}

		return t;
	}


	int getBFS(vvi &forest,vi start,vi end){

		vvi distance(m, vi(n, -1));

		queue<pair<int,int> > q;
		q.push({start[0], start[1]});
		distance[start[0]][start[1]] = 0;
		while(!q.empty()){
			int x = q.front().first, y = q.front().second; q.pop();
			if(forest[x][y] == forest[end[0]][end[1]]) return distance[x][y];

			for(int k = 0;k < 4;k++){
				int new_x = x + dire_x[k], new_y = y + dire_y[k];
				if(isValid(new_x, new_y) && distance[new_x][new_y] == -1 && forest[new_x][new_y]){
					distance[new_x][new_y] = distance[x][y] + 1;
					if(forest[new_x][new_y] == forest[end[0]][end[1]]) return distance[new_x][new_y];
					q.push({new_x, new_y});
				}
			}

		}

		return -1;
	}

	int cutOffTree(vvi &forest){
		m = forest.size(), n = forest[0].size();

		priority_queue<vi, vector<vi>, greater<vi> > pq;

		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(forest[i][j] > 1){
					pq.push({forest[i][j], i, j});
				}
			}
		}
		visited = vvb(m, vb(n, false));
		int steps = 0;
		vector<int> last = {0, 0};
		while(!pq.empty()){
			vi curr = pq.top(); pq.pop();
			int res = BFS(forest, last, {curr[1], curr[2]});
			if(res == -1) return -1;
			steps += res, last = {curr[1], curr[2]};
		}
		return steps;

	}
};


int main(){
	int n, m;
	cin >> n >> m;
	vvi forest(n, vi(m));
	for(vi &a: forest) for(int &b: a) cin >> b;
	cout << Solution().cutOffTree(forest) << "\n";
	return 0;
}



