#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>

using namespace std;
#define vi vector<int>
#define vb vector<bool>
#define vvi vector<vi>
#define vvb vector<vb>

vector<vector<int> > arr;

int dir_x[] = {-1, 0, 1, 0};
int dir_y[] = {0, 1, 0, -1};

bool isValid(int &x,int &y,int &r,int &c){
	return x >= 0 && y >= 0 && x < r && y < c;
}

int timeToRotteenEggs(vvi &arr,int nonRoutenCount){
	int r = arr.size(), c = arr[0].size(), time = 0;
	vvb visited(r, vb(c, false));
	queue<pair<int,int> > pendingNodes;
	for(int i=0;i<r;i++) for(int j=0;j<c;j++) if(arr[i][j] == 2) visited[i][j] = true, pendingNodes.push({i, j});

	while(pendingNodes.size() && nonRoutenCount > 0){
		int sz_t = pendingNodes.size();
		while(sz_t--){
			int curr_x = pendingNodes.front().first, curr_y = pendingNodes.front().second;
			pendingNodes.pop();
			for(int k=0;k<4;k++){
				int new_x = curr_x + dir_x[k], new_y = curr_y + dir_y[k];
				if(isValid(new_x, new_y, r, c) && !visited[new_x][new_y] && arr[new_x][new_y] == 1){
					nonRoutenCount--, visited[new_x][new_y] = true, pendingNodes.push({new_x, new_y});
				}
			}
		}
		time++;
	}

	return nonRoutenCount == 0?time:-1;
}

int main(){
	int t, r, c;
	cin >> t;
	while(t--){
		cin >> r >> c;
		swap(r, c);
		arr.clear(); arr.resize(c, vector<int> (r));
		int nonRoutenCount = 0;
		for(vector<int> &b: arr) for(int &a: b) {cin >> a; if(a == 1) nonRoutenCount++;}
		cout << timeToRotteenEggs(arr, nonRoutenCount) << "\n";
	}
	return 0;
}



