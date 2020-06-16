#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

vector<vector<int> > getSkyLine(vector<vector<int> >& buildings)
{
	vector<vector<int> > res;
	priority_queue<pair<int,int> > liveBlg;//first: height, second: ending edge
	int len = buildings.size();
	int cur = 0, curX, curH;
	while(cur < len || !liveBlg.empty())
	{
		curX = liveBlg.empty()?buildings[cur][1]: liveBlg.top().second;

		if(cur >= len || buildings[cur][0] > curX)
		{
			while(!liveBlg.empty() && (liveBlg.top().second <= curX)) liveBlg.pop();
		}
		else
		{
			curX = buildings[cur][0];
			while(cur < len && buildings[cur][0] == curX)
			{
				liveBlg.push(make_pair(buildings[cur][2], buildings[cur][1]));
				cur++;
			}
		}
		curH = liveBlg.empty()?0:liveBlg.top().first;
		if(res.empty() || (res.back()[1] != curH)) res.push_back(vector<int> {curX, curH});
	}
	return res;
}

vector<vector<int> > getSkyLine2(vector<vector<int> > &buildings)
{
	multimap<int,int> coords;
	for(const vector<int> &bd: buildings)
	{
		coords.emplace(bd[0], bd[2]);
		coords.emplace(bd[1], -bd[2]);
	}

	multiset<int> height = {0};
	map<int,int> corners;

	for(const pair<int,int> &p: coords)
	{
		if(p.second > 0)
		{
			height.emplace(p.second);
		}
		else
		{
			height.erase(height.find(-p.second));
		}

		int curY = *height.rbegin();
		corners[p.first] = curY;
	}

	vector<vector<int> > res;
	for(const pair<int,int> &p: corners)
	{
		if(res.empty() || (res.back()[1] != p.second)) res.push_back(vector<int> {p.first, p.second});
	}
	return res;
}

int main()
{
	multiset<int> m;
	m.insert(30);
	m.insert(30);
	m.insert(20);
	m.insert(20);
	m.insert(10);
	m.emplace(10);
	m.erase(m.find(10));
	for(auto it = m.begin();it != m.end();it++) cout << *it << " ";
	cout << endl;
	multimap<int,int> mp;
	mp.emplace(2,3);
	mp.emplace(1,5);
	mp.emplace(10,12);
	for(auto it = mp.begin();it != mp.end();it++)
	{
		cout << it->first << " " << it->second << endl;
	}
	vector<vector<int> > a;
	a.push_back(vector<int> {10,11});
	cout << a[0].size() << endl;
	return 0;
}

