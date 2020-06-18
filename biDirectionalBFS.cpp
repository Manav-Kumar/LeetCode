#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <queue>

using namespace std;

// This Question is similar to WordLadder1 it's just another approach to solve it.

int lengthLadder(string beginWord,string endWord, unordered_set<string>& wordList)
{
	if(wordList.find(endWord) == wordList.end()) return 0;
	map<string, unordered_set<string> > mp;
	for(string w: wordList)
	{
		for(int i = 0;i < w.size();i++)
		{
			string temp = w;
			temp[i] = '*';
			mp[temp].insert(w);
		}
	}
	map<string,int> visited1, visited2;
	queue<string> pending1, pending2;
	visited1[beginWord] = 1 , visited2[endWord] = 1;
	pending1.push(beginWord), pending2.push(endWord);
	pending1.push("\0"), pending2.push("\0");
	int level1 = 1, level2 = 1;
	bool turn = 1;
	while(!pending1.empty() && !pending2.empty())
	{
		string s;
		if(turn) s = pending1.front(), pending1.pop();
		else s = pending2.front(), pending2.pop();

		if(s == "\0")
		{
			if(turn)
			{
				if(pending1.empty()) return 0;
				pending1.push("\0"), level1++;
				turn = (turn+1)%2;
				continue;
			}
			else
			{
				if(pending2.empty()) return 0;
				pending2.push("\0"), level2++;
				turn = (turn+1)%2;
				continue;
			}
		}

		for(int i = 0;i < s.size();i++)
		{
			string temp = s;
			temp[i] = '*';
			for(string w: mp[temp])
			{
				if(turn)
				{
					if(visited2.find(w) != visited2.end()) return level1 + visited2[w];
					if(visited1.find(w) == visited1.end()) visited1[w] = level1+1 , pending1.push(w);
				}
				else
				{
					if(visited1.find(w) != visited1.end()) return level2 + visited1[w];
					if(visited2.find(w) == visited2.end()) visited2[w] = level2+1 , pending2.push(w);
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
	cout << lengthLadder(beginWord, endWord, wordList) << endl;
	return 0;
}

