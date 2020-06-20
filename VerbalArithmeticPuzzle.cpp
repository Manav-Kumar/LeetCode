#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <unordered_set>

using namespace std;

bool helper(unordered_set<char> alp, bool *booked,map<char,int> sol, unordered_set<char> startAlp,
		vector<string>& words,string result)
{
	if(alp.empty())
	{
		//Evaluate
		int leftSum = 0, rightSum = 0;
		for(string s: words)
		{
			int left = 0;
			for(char c: s) left = left*10 + sol[c];
			leftSum += left;
		}
		for(char c: result) rightSum = rightSum*10 + sol[c];
		return leftSum == rightSum;
	}
	char c = *(alp.begin());
	alp.erase(c);
	for(int i = 0;i<10;i++)
	{
		if(booked[i] || (i == 0 && startAlp.find(c) != startAlp.end())) continue;
		sol[c] = i, booked[i] = true;
		if(helper(alp, booked, sol, words, result)) return true;
		booked[i] = false;
	}
	return false;
}

bool isSolvable(vector<string>& words,string result)
{
	unordered_set<char> alp;
	unordered_set<char> startAlp;
	for(string s: words)
	{
		startAlp.insert(s[0]);
		if(s.size() > result.size()) return false;
		for(char c: s) alp.insert(c);
	}
	for(char c: result) alp.insert(c);
	bool *booked = new bool[10]();
	fill(booked, booked+10, false);
	bool ans = helper(alp, booked, map<char,int>(), startAlp, words, result);
	delete []booked;
	return ans;
}

int main()
{
	int n;
	vector<string> words;
	string result;
	cin >> n;
	words.resize(n);
	for(string &s: words) cin >> s;
	cin >> result;
	cout << isSolvable(words, result) << endl;
	return 0;
}



