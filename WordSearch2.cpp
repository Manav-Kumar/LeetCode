#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <unordered_set>

using namespace std;

bool helper(vector<vector<char> >& board,string s,bool **visited,int n,int m,int i,int j)
{
	if(s.empty()) return true;
	if(i < 0 || j < 0 || i >= n || j >= m || visited[i][j] || s[0] != board[i][j])
		return false;

	visited[i][j] = true;
	if(helper(board, s.substr(1), visited, n,m, i+1,j)) return true;
	if(helper(board, s.substr(1), visited, n,m, i, j+1)) return true;
	if(helper(board, s.substr(1), visited, n,m, i-1,j)) return true;
	if(helper(board, s.substr(1), visited, n,m, i,j-1)) return true;

	visited[i][j] = false;
	return false;
}

bool helper2(vector<vector<char> >& board,string s,bool **visited,int n,int m)
{
	for(int i =  0;i < n;i++)
	{
		for(int j = 0;j < m;j++) if(helper(board, s, visited, n, m,i,j)) return true;
	}
	return false;
}

vector<string> findWords(vector<vector<char> >& board, vector<string>& words)
{
	if(board.empty()) return vector<string>();
	int n = board.size(), m = board[0].size();
	vector<string> ans;
	for(string s: words)
	{
		bool **visited = new bool*[n];
		for(int i = 0;i<n;i++) visited[i] = new bool[m](), fill(visited[i], visited[i]+m, false);
		if(helper2(board, s, visited,n,m)) ans.push_back(s);
		for(int i = 0;i<n;i++) delete []visited[i];
		delete []visited;
	}
	return ans;
}

int main()
{
	vector<vector<char> > board;
	int n,m;
	cin >> n >> m;
	board.resize(n);
	for(int i = 0;i < n;i++)
	{
		board[i].resize(m);
		for(int j = 0;j < m;j++) cin >> board[i][j];
	}
	cin >> m;
	vector<string> words;
	words.resize(m);
	for(string &s: words) cin >> s;
	vector<string> ans = findWords(board, words);
	for(string s: ans) cout << s << endl;
	return 0;
}

