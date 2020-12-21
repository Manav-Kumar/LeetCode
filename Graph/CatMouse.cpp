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

vvvi visited;
int n;
int dp[100][50][50];

int catMouseGameHelper(vvi &graph, int mouseNode = 1, int catNode = 2,int turn = 0){
	if(turn == 2*n) return 0;
	int &result = dp[turn][mouseNode][catNode];
	if(catNode == mouseNode){
		//	Cat Wins
		return result = -10;
	}
	if(mouseNode == 0){
		//	Mouse Wins
		return result = 10;
	}
	if(result != -1) return result;

	int ans;
	if(turn%2 == 0){//Mouse turn
		ans = -10;
		for(int &next: graph[mouseNode]){
			ans = max(ans, catMouseGameHelper(graph, next, catNode, turn + 1));
			if(ans == 10) return result = 10;
		}
	}
	else if(turn%2){
		ans = 10;
		for(int &next: graph[catNode]){
			if(next != 0) ans = min(ans, catMouseGameHelper(graph, mouseNode, next, turn + 1));
			if(ans == -10) return result = -10;
		}
	}

	result = ans;

	return ans;
}


int catMouseGame(vvi &graph){
	n = graph.size();
	visited.clear(), visited.resize(2*n, vvi(n, vi(n, -1)));
	int ans = catMouseGameHelper(graph);
	if(ans == 10) return 1;
	else if (ans == -10) return 2;
	else return 0;
}

int main(){
	int n, k;
	cin >> n;
	vvi graph(n, vi());
	for(vi &a: graph){
		cin >> k;
		a.resize(k);
		for(int &b: a) cin >> b;
	}
	cout << catMouseGame(graph) << "\n";
	return 0;
}

