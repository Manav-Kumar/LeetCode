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


int bfs(string board,unordered_map<char,int> count)
{
	unordered_set<string> visited;
	visited.insert(board);
	queue<string> q;
	q.push(board);
	while(!q.empty()){
		string s = q.front(); q.pop();


	}
	return 0;
}

int dfs(string board,unordered_map<char,int> count){
	if(board.empty()) return 0;

	int i = 0, len = 1, ans = INT_MAX;
	char color;
	while(i < board.size())
	{
		len = 0, color = board[i];
		int start = i;
		while(i < board.size() && board[i] == color){
			i++, len++;
		}
		if(len + count[color] >= 3){
			string temp = board.substr(0, start) + (i == board.size()?"": board.substr(i));
			unordered_map<char,int> copy(count.begin(), count.end());
			if(len < 3) copy[color] -= 3 - len;
			int a1 = dfs(temp, copy);
			if(a1 != INT_MAX) a1 += max(0, 3 - len);
			ans = min(ans, a1);
		}

	}

	return ans;
}

int findMinStep(string board,string hand){
	unordered_map<char,int> count;
	for(char &c: hand) count[c] += 1;
	int ans = dfs(board, count);
	if(ans == INT_MAX) return -1;
	return ans;
}

int main(){
	string board, hand;
	cin >> board >> hand;
	cout << findMinStep(board, hand) << "\n";
	return 0;
}







