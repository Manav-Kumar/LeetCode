#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_map>

using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define rep(i,a,b) for(int i=a;i<b;i++)

bool canGo(int &x,int &y,int &n,int &m,vector<vector<bool > > &visited,vector<vector<int> >& grid)
{
	if(x < 0 || y < 0 || x >= n || y >= m || visited[x][y] || grid[x][y] == -1) return false;
	return true;
}

int dirx[] = {1,0,-1,0};
int diry[] = {0,-1,0,1};

int helper(vector<vector<int> >& grid,int x,int y,int enx,int eny,vector<vector<bool> >& visited,
	int count)
{
	count--;
	if(x == enx && y == eny && count == 0) return 1;
	int n = grid.size(), m = grid[0].size(), total = 0;
	visited[x][y] = true;
	for(int i=0;i<4;i++)
	{
		int new_x = x + dirx[i], new_y = y + diry[i];
		if(canGo(new_x,new_y,n,m,visited,grid))
			total += helper(grid, new_x, new_y, enx, eny, visited,count);
	}
	visited[x][y] = false;
	return total;
}

int uniquePath3(vector<vector<int> >& grid)
{
	int n = grid.size(),m = grid[0].size() ,x,y,enx,eny,count = 0;
	for(int i = 0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(grid[i][j] == 1) x=i, y=j;
			else if(grid[i][j] == 2) enx=i,eny=j;

			if(grid[i][j] != -1) count++;
		}
	}
	vector<vector<bool > > visited(n, vector<bool>(m,false));
	return helper(grid, x,y,enx,eny,visited,count);
}

// Another Problem 
/*
		WORD BREAK II
*/

vector<string> wordBreakHelper(string s,unordered_set<string>& wordDict, string word="",int idx = 0)
{
	if(idx == s.size())
	{
		if(wordDict.find(word) == wordDict.end()) return vector<string>();
		return vector<string>{word};
	}
	vector<string> smallAns1 = wordBreakHelper(s,wordDict,word + s[idx],idx+1);
	if(wordDict.find(word) != wordDict.end())
	{
		string temp = "";
		temp += s[idx];
		vector<string> smallAns2 = wordBreakHelper(s,wordDict,temp,idx+1);
		if(!smallAns2.empty())
		{
			for(string &s: smallAns2) s = word + " " + s;
			smallAns1.insert(smallAns1.end(), smallAns2.begin(), smallAns2.end());
		}
	}

	return smallAns1;
	
}


vector<string> wordBreakHelper2(string s,unordered_set<string>& wordDict,
			unordered_map<int, vector<string> >& dp,int idx)
{
	if(dp.count(idx) == 0)
	{
		for(int i = idx-1;i >= 0;i--)
		{
			string tail = s.substr(i,idx-i);
			if(wordDict.count(tail) == 0) continue;
			for(string s: wordBreakHelper2(s,wordDict,dp,i))
			{
				dp[idx].push_back(s.append(s == ""?tail:" "+tail));
			}
		}
	}
	return dp[idx];
}

vector<string> wordBreak(string s,unordered_set<string>& wordDict)
{
	// unordered_map<int,vector<string> > dp;
	// dp[0] = {""};
	// return wordBreakHelper2(s,wordDict,dp,s.length());
	return wordBreakHelper(s, wordDict);
}


int main()
{
	int n;
	cin >> n;
	string s;
	unordered_set<string> wordDict;
	while(n--)
	{
		string k;
		cin >> k;
		wordDict.insert(k);
	}
	cin >> s;
	vector<string> ans = wordBreak(s,wordDict);
	for(string s: ans) cout << s << "\n";
	return 0;


}

