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

int helper(vector<string>& stickers,map<char,int> target,map<char,int> curr,int idx = 0,
		int satisfied = 0)
{
	if(satisfied == (1<<target.size())-1) return 0;
	if(idx == stickers.size()) return INT_MAX;

	int ct = 0;
	string s = stickers[idx];
	int ans = INT_MAX;
	while(1)
	{
		bool isValid = false;
		for(char c:s)
		{
			if(target.find(c) == target.end()) continue;
			curr[c] += (ct == 0)?0:1;
			if(curr[c] <= target[c]) isValid = true;
			if(curr[c] >= target[c])
			{
				int temp = distance(target.begin(), target.find(c));
				satisfied |= (1<<temp);
			}
		}
		int smallAns = helper(stickers, target, curr, idx+1, satisfied);
		if(smallAns != INT_MAX) smallAns += ct;
		ans = min(ans ,smallAns );
		if(!isValid) break;
		ct++;
	}
	return ans;
}


int minStickers(vector<string>& stickers, string s)
{
	map<char,int> target;
	for(char c: s) target[c] += 1;
	int n = stickers.size();
	vector<map<char,int> > present;
	present.resize(n);
	for(int i=0;i<n;i++) for(char c: stickers[i]) present[i][c] += 1;
	vector<unordered_set<int> > dominate(n);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i == j) continue;
			bool isD = true;
			for(char c: s) if(present[i][c] < present[j][c]) isD = false;
			if(isD) dominate[i].insert(j);
		}
	}

	vector<int> removeIndex(n, false);
	for(int i = 0;i<n;i++)
	{
		if(!removeIndex[i])
		{
			for(auto it = dominate[i].begin();it!=dominate[i].end();it++)
				if(!removeIndex[*it]) helper2(dominate, removeIndex, *it);
		}
	}
	for(int i = n-1;i >= 0;i--)
	{
		if(removeIndex[i]) stickers.erase(stickers.begin() + i);
	}
	for(int i = 0;i < stickers.size();i++) cout << stickers[i] << endl;
	int ans = helper(stickers, target, map<char,int>());
	if(ans == INT_MAX) return -1;
	return ans;
}


int helper3(vector<vector<int> > &mp,unordered_map<string,int>& dp,string target)
{
	if(dp.count(target)) return dp[target];
	int ans = INT_MAX, n = mp.size();
	vector<int> tar(26,0);
	for(char c: target) tar[c - 'a'] += 1;
	for(int i=0;i<n;i++)
	{
		// Ensuring 1st element of target must be in the current word
		if(mp[i][target[0] - 'a'] == 0) continue;

		string s;
		for(int j=0;j<26;j++)
		{
			if(tar[j] - mp[i][j] > 0) s += string(tar[j] - mp[i][j], 'a' + j);
		}
		int temp = helper3(mp,dp,s);
		if(temp != -1) ans = min(ans, temp+1);
	}
	ans = (ans == INT_MAX)?-1:ans;
	dp[target] = ans; 
	return ans;
}


int minStickers3(vector<string>& stickers,string s)
{
	int n = stickers.size();
	vector<vector<int> > mp(n, vector<int>(26,0));
	for(int i=0;i<n;i++)
	{
		for(char c: stickers[i]) mp[i][c - 'a'] += 1;
	}
	unordered_map<string,int> dp;
	dp[""] = 0;
	return helper3(mp, dp, s);
}


// BFS Approach
// IN BFS IS USED WHERE WE USUALLY NEED THE SHORTEST PATH, JUST NEED TO THINK WHAT SHOULD NODE THE STORE

int minStickers4(vector<string>& stickers, string target)
{
	cout << "enterd" << endl;
	int m = stickers.size(), n = target.size();
	vector<vector<int> > mp(m, vector<int>(26, 0));
	for(int i=0;i<m;i++) for(char c: stickers[i]) mp[i][c - 'a'] += 1;
	queue<int> q;
	q.push((1<<n)-1);
	int level = 0;
	unordered_set<int> vis;
	while(!q.empty())
	{
		++level;
		for(int sz = q.size();sz > 0;sz--)
		{
			int curr_tar = q.front(); q.pop();
			if(vis.count(curr_tar)) continue;
			else vis.insert(curr_tar);
			//Try to remove the characters from target starting from right going towards left
			int start = 0;
			while(start < n)
			{
				if((curr_tar>>start)&1) break;
				else ++start;
			}

			for(int i = 0;i < m;i++)
			{
				if(mp[i][target[n-1-start] - 'a'] == 0) continue;
				int nxt_tar = curr_tar;
				for(char c: stickers[i])
				{
					for(int j=start;j<n;j++)
					{
						if(target[n-1-j] == c && ((nxt_tar>>j)&1))
						{
							nxt_tar ^= (1<<j);
							break;
						}
					}
				}

				if(nxt_tar == 0) return level;
				q.push(nxt_tar);
			}
		}
	}
	return -1;
}


int main()
{
	int n;
	cin >> n;
	vector<string> stickers;
	string target;
	stickers.resize(n);
	for(string &s: stickers) cin >> s;
	cin >> target;
	cout << minStickers4(stickers, target) << endl;
	return 0;
}




