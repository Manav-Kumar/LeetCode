#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

//We need to remove duplicate letters making sure the resultant is smallest in lexographical order

typedef map<char,vector<int> >::iterator mpvt;

// string helper(string s,mpvt &mp,mpvt it, vector<int> res)
// {
//     if(it == mp.end())
//     {
//         sort(res.begin(), res.end());
//         string ans="";
//         for(int pos: res) ans += s[pos];
//         return ans;
//     }
//     string ans = "";
//     for(int pos: it->second)
//     {
//         res.push_back(pos);
//         string a1 = helper(s, mp, next(it), res);
//         res.pop_back();
//         if(ans == "" || a1 < ans) ans = a1;
//     }
//     return ans;
// }


// string removeDuplicateLetters(string s)
// {
//     mpvt mp;
//     for(int i = 0;i < s.size();i++) mp[s[i]].push_back(i);
//     return helper(s, mp, mp.begin(), vector<int> ());
// }


string removeDuplicateLetters2(string s)
{
	string res(27,'\0');
	vector<int> count(26,0);
	bool visited[26];
	fill(visited, visited+26, false);
	for(char c: s) ++count[c - 'a'];
	int size = 0;
	for(char &c: s)
	{
		count[c - 'a']--;
		if(visited[c - 'a']) continue;
		int j = size - 1;
		for(;j >= 0;j--)
		{
			if(c > res[j] || !count[res[j] - 'a']) break;
			else visited[res[j] - 'a'] = false;
		}
		res[++j] = c;
		visited[c - 'a'] = true;
		size = j+1;
	}
	return res.substr(0, size);
}


int main()
{
	string s;
	cin >> s;
	cout << removeDuplicateLetters2(s) << endl;
	return 0;
}

