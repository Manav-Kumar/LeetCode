#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <queue>
#include <map>
#include <set>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)

void helper(bool b[][9])
{
	b[4][2] = true;
}

int main()
{
	vector<int*> v;
	v.resize(10, NULL);
	cout << v.size() << endl;
	string s;
	s.push_back('a');
	s.push_back('b');
	s.push_back('c');
	cout << s << endl;
	int dirx[] = {1,23,4,5};
	int used = 15;
	if(used == (1<<4)-1) cout << "ok";
	map<int,int> ct;
	ct[3] = 10;
	ct[4] = 20;
	ct[5] = 30;
	for(auto it = ct.begin();it!=ct.end();)
	{
		cout << it->first << " " << it->second << endl;
		if(it->first == 4) it = ct.erase(it);
		else ++it;
	}
	map<int,int> mp;
	mp[2] = 20;
	mp[3] = 10;
	mp[4] = 90;
	cout << distance(mp.begin(), mp.find(5)) << endl;
	vector<int> vt;
	vt.push_back(3);
	vt.push_back(12);
	vt.erase(vt.begin() + 1);
	cout << vt.size();
	string ans = string(1,'c') + 'd';
	cout << ans << endl;
	bool b[9][9] = {};
	helper(b);
	cout << b[4][2] << endl;
	vector<string> st(2, "manav");
	for(string &s: st) s = "aa" + s;
	cout << st[0] << "\n";
	vector<string> kt;
	kt.insert(kt.end(), st.begin(), st.end());
	return 0;
}
