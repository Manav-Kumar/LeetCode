#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <queue>
using namespace std;


int ladderLength(string beginWord,string endWord,unordered_set<string>& wordList)
{
	queue<vector<string> > pending;
	unordered_set<string> visited;
	pending.push({beginWord});
	int level = 1;
	while(!pending.empty())
	{
		vector<string> path = pending.front();
		pending.pop();
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
			for(char c = 'a'; c <= 'z';++c)
			{
				news[i] = c;
				if(wordList.find(news) != wordList.end())
				{
					vector<string> newpath = path;
					newpath.push_back(news);
					visited.insert(news);
					if(news == endWord) return level+1;
					else pending.push(newpath);
				}
			}
		}
	}
	return 0;
}


// Another Approach
int ladderLength2(string beginWord,string endWord,unordered_set<string> wordList)
{
	map<string,unordered_set<string> > mp;
	for(string w: wordList)
	{
		for(int i = 0;i < w.size();i++)
		{
			string temp = w;
			temp[i] = '*';
			mp[temp].insert(w);
		}
	}
	unordered_set<string> visited;
	visited.insert(beginWord);
	queue<string> pending;
	pending.push(beginWord);
	int level = 1;
	pending.push("\0");
	while(!pending.empty())
	{
		string s = pending.front();
		pending.pop();
		if(s == "\0")
		{
			if(pending.empty()) return 0;
			level++, pending.push("\0");
			continue;
		}
		for(int i = 0;i < s.size();i++)
		{
			string temp = s;
			temp[i] = '*';
			for(string w: mp[temp])
			{
				if (visited.find(w) == visited.end())
				{
					cout << w << endl;
					visited.insert(w), pending.push(w);
					if(w == endWord) return level+1;
				}
			}
		}
	}
	return 0;
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
	cout << ladderLength2(beginWord, endWord, wordList) << endl;
	return 0;
}



