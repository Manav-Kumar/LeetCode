#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


#define vvi vector<vector<int> > 
#define vi vector<int>

bool compare(vector<int> newInterval,vector<int> givenInt)
{
	return givenInt[1] > newInterval[1];
}

vvi insertFunc2(vvi intervals,vi newInterval)
{
	auto it1 = upper_bound(intervals.begin(), intervals.end(), newInterval);
	auto it2 = upper_bound(intervals.begin(), intervals.end(), newInterval, compare);
	
	if(it1 != intervals.begin() && prev(it1)->at(1) >= newInterval[0])
	{
		newInterval[0] = (--it1)->at(0);
	}
	if(it2 != intervals.end() && it2->at(0) <= newInterval[1])
	{
		newInterval[1] = (it2++)->at(1);
	}
	vvi res;
	for(auto it = intervals.begin(); it!=it1;it++) res.push_back(*it);
	res.push_back(newInterval);
	for(auto it = it2; it != intervals.end();it++) res.push_back(*it);
	return res;
}

vvi insertFunc(vvi intervals, vi newInterval)
{
	auto it = upper_bound(intervals.begin(), intervals.end(), newInterval);
	if(it != intervals.begin() && (--it)->at(1) < newInterval[0]) ++it;

	while(it != intervals.end() && it->at(0) <= newInterval[1])
	{
		newInterval[0] = min(newInterval[0], it->at(0));
		newInterval[1] = max(newInterval[1], it->at(1));
		it = intervals.erase(it);
	}

	intervals.insert(it,newInterval);
	return intervals;
}


vvi insertFunc4(vvi intervals, vi newInterval)
{
	auto it1 = upper_bound(intervals.begin(), intervals.end(), newInterval);
	auto it2 = upper_bound(intervals.begin(), intervals.end(), newInterval, compare);

	if(it1 != intervals.begin() && prev(it1)->at(1) >= newInterval[0]) newInterval[0] = (--it1)->at(0);
	if(it2 != intervals.end() && it2->at(0) <= newInterval[1]) newInterval[1] = (it2++)->at(1);

	it2 = intervals.erase(it1, it2);
	intervals.insert(it2, newInterval);
	return intervals;
}

vvi insertFunc3(vvi intervals,vi newInterval)
{
	vvi res;
	auto it = intervals.begin();
	for(;it != intervals.end();it++)
	{
		if(it->at(1) < newInterval[0]) res.push_back(*it);
		else if(newInterval[1] < it->at(0)) break;
		else
		{
			newInterval[0] = min(newInterval[0], it->at(0));
			newInterval[1] = max(newInterval[1], it->at(1));
		}
	}
	res.push_back(newInterval);
	for(;it != intervals.end();it++) res.push_back(*it);
	return res;
}

vvi MergeIntervals(vvi &intervals)
{
	if(intervals.empty()) return vvi();
	vvi res;
	sort(intervals.begin(), intervals.end());
	auto it = intervals.begin();
	res.push_back(*it);
	++it;
	for(;it!=intervals.end();it++)
	{
		if(res.back()[1] >= it->at(0)) res[res.size()-1][1] = max(res[res.size()-1][1],it->at(1));
		else res.push_back(*it);
	}
	return res;
}

int main()
{
	int n;
	cin >> n;
	vvi intervals;
	intervals.resize(n);
	for(vi &a: intervals)
	{
		a.resize(2);
		cin >> a[0] >> a[1];
	}
	
	vvi ans = MergeIntervals(intervals);
	for(vi &a: ans) cout << a[0] << " " << a[1] << endl;
	return 0;
}