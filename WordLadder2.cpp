#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>


using namespace std;;

// Here we don't have to find all the paths rather only the paths which are shortest.
// Therefore instead of DFS, apply BFS

#define rep(i,a,b) for(int i = a;i < b;i++)

void helper(string beginWord, string endWord, vector<string>& wordList, vector<map<int,int> > index,
					bool *visited)
{
	if(beginWord == endWord)
	{
		cout << "Got" << endl;
		return;
	}
	map<int,int> cal;
	rep(i, 0, beginWord.length())
	{
		map<int,int> temp = index[beginWord[i] - 'a'];
		for(auto it = temp.begin(); it != temp.end(); it++)
		{
			cal[it->first] += it->second;
		}
	}
	for(auto it = cal.begin(); it != cal.end();it++)
	{
		if(it->second == beginWord.length()-1 && !visited[it->first])
		{
			visited[it->first] = true;
			helper(wordList[it->first], endWord, wordList, index, visited);
			visited[it->first] = false;
		}
	}
	return;
}


vector<vector<string> > helper2(string beginWord,string endWord,unordered_set<string>& wordList)
{
	queue<vector<string> > pending;
	vector<vector<string> > ans;
	pending.push({beginWord});
	unordered_set<string> visited;
	int minLevel = INT_MAX, level = 1;
	while(!pending.empty())
	{
		vector<string> path = pending.front();
		pending.pop();
		if(path.size() > minLevel) break;
		if(path.size() > level)
		{
			for(string w: visited) wordList.erase(w);
			visited.clear();
			level = path.size();
		}

		string last = path.back();
		for(int i = 0;i < last.size();i++)
		{
			string news = last;
			for(char c = 'a';c <= 'z';++c)
			{
				news[i] = c;
				if(wordList.find(news) != wordList.end())
				{
					vector<string> newpath = path;
					newpath.push_back(news);
					visited.insert(news);
					if(news == endWord)
					{
						minLevel = level;
						ans.push_back(newpath);
					}
					else pending.push(newpath);
				}
			}
		}
	}
	return ans;
}



void findLadders(string beginWord, string endWord, vector<string>& wordList) {
	wordList.push_back(beginWord);
	vector<map<int,int> > index(26);
	rep(i,0,wordList.size())
	{
		string s = wordList[i];
		rep(j, 0, s.length())
		{
			index[s[j] - 'a'][i] = index[s[j] - 'a'][i] + 1;
		}
	}
	rep(i, 0, 26)
	{
		map<int,int> temp = index[i];
		if(temp.empty()) continue;
		cout << char(i + 'a') << endl;
		for(auto it=temp.begin(); it!=temp.end();it++) cout << it->first << " " << it->second << endl;
	}
	bool *visited = new bool[wordList.size()]();
	fill(visited, visited + wordList.size(), false);

	helper(beginWord, endWord, wordList, index, visited);
}

int main()
{
	unordered_set<string> wordList;
	string beginWord, endWord;
	cin >> beginWord >> endWord;
	cout << "Enter the size of dict" << endl;
	int n;
	cin >> n;
	while(n--)
	{
		string s;
		cin >> s;
		wordList.insert(s);
	}
	vector<vector<string> > ans = helper2(beginWord, endWord, wordList);
	for(int i = 0;i < ans.size();i++)
	{
		for(int j = 0; j < ans[i].size();j++) cout << ans[i][j] << " ";
		cout << "\n";
	}
	return 0;
}