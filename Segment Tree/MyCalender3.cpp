#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <cmath>
#include <math.h>
#include <unordered_set>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vl vector<long>
#define vll vector<long long>
#define vc vector<char>
#define vvc vector<vc>
#define vvi vector<vector<int> >
#define vvl vector<vl>
#define vvll vector<vll>
#define vvb vector<vector<bool> >


class MyCalendarThree
{
public:
	map<int,int> mp;
	MyCalendarThree() {}

	int book(int s,int e)
	{
		mp[s]++;
		mp[e]--;
		auto it = mp.begin();
		int ans = 0, open = 0;
		while(it != mp.end())
		{
			open += it->second;
			ans = max(ans, open);
			it++;
		}
		return ans;
	}
};

int main()
{
	int st,en;
	MyCalendarThree mc3;
	for(int i=0;i<6;i++)
	{
		cin >> st >> en;
		cout << mc3.book(st,en) << "\n";
	}
	return 0;
}