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

// This implementation can't solve big queries, as we are repeating the work for the words
// 		starting with same prefix
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


//Implementing with the helpe of Tries

class node
{
public:
	bool isTerm;
	vector<node*> next;
	node(): isTerm(false), next(vector<node*>(26,NULL))
	{}
};

class Trie
{
public:
	node* root;
	vector<vector<bool> > visited;
	int dirx[4] = {-1,0,1,0};
	int diry[4] = {0,1,0,-1};
	Trie(int n,int m): root(new node()), visited(vector<vector<bool> >(n, vector<bool>(m,false)))  
	{}
	~Trie()
	{
		del_tree(root);
	}

	void del_tree(node* temp)
	{
		for(int i = 0;i<26;i++)
		{
			if(temp->next[i] != NULL) del_tree(temp->next[i]);
		}
		delete temp;
	}

	void insert(string word)
	{
		node* temp = root;
		for(int i = 0;i < word.size();i++)
		{
			int c = word[i] - 'a';
			if(temp->next[c] == NULL) temp->next[c] = new node();
			temp = temp->next[c];
		}
		temp->isTerm = true;
	}

	void gridSearch(const vector<vector<char> >& board,int i,int j,int n,int m,
					vector<string>& ret,node *curNode,string res = "")
	{

		visited[i][j] = true;
		res.push_back(board[i][j]);
		if(curNode->isTerm) ret.push_back(res), curNode->isTerm = false;

		for(int k = 0;k<4;k++)
		{
			int new_i = i + dirx[k], new_j = j + diry[k];
			if(new_i >= 0 && new_j >= 0 && new_i < n && new_j < m && !visited[new_i][new_j] &&
					curNode->next[board[new_i][new_j] - 'a'] != NULL)
			{
				gridSearch(board, new_i,new_j,n,m,ret,curNode->next[board[new_i][new_j] - 'a'], res);
			}
		}
		visited[i][j] = false;
	}

};


vector<string> findWords2(vector<vector<char> >& board, vector<string>& words)
{
	vector<string> ret;
	if(board.size() == 0 || board[0].size() == 0 || words.empty()) return ret;
	int n = board.size(), m = board[0].size();
	Trie trie(n,m);
	for(string w: words) trie.insert(w);
	for(int i = 0;i<n;++i)
	{
		for(int j=0;j<m;++j)
		{
			if(trie.root->next[board[i][j] - 'a'] != NULL)
			{
				trie.gridSearch(board,i,j,n,m,ret, trie.root->next[board[i][j] - 'a']);
			}
		}
	}
	return ret;
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
	vector<string> ans = findWords2(board, words);
	for(string s: ans) cout << s << endl;
	return 0;
}

