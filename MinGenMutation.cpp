#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <unordered_set>

using namespace std;

int minMutation(string start,string end,unordered_set<string>& bank)
{
	char mutations[] = {'A','C','G','T'};
	unordered_set<string> visited;
	queue<string> pending;
	pending.push(start), pending.push("\0");
	visited.insert(start);
	int level = 1;
	while(!visited.empty())
	{
		string s = pending.front();
		pending.pop();
		if(s == "\0")
		{
			if(pending.empty()) return -1;
			pending.push("\0"), level++;
			continue;
		}
		for(int i = 0;i < s.size();i++)
		{
			for(char c: mutations)
			{
				string temp = s;
				temp[i] = c;
				if(bank.find(temp) != bank.end() && visited.find(temp) == visited.end())
				{
					if(temp == end) return level;
					visited.insert(temp);
					pending.push(temp);
				}
			}
		}
	}
	return -1;
}

int main()
{
	string start, end, s;
	cin >> start >> end;
	int n;
	cin >> n;
	unordered_set<string> bank;
	while(n--)
	{
		cin >> s;
		bank.insert(s);
	}
	cout << minMutation(start, end, bank);
	return 0;
}