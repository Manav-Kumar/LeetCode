#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long

class MajorityChecker
{
public:
	MajorityChecker(vector<int>& arr): arr(arr)
	{
		rep(i, 0, arr.size()) mp[arr[i]].push_back(i);
	}

	int query(int left,int right,int threshold)
	{
		rep(i,0,20)
		{
			int randIdx = rand()%(right - left + 1) + left;
			int ele = arr[randIdx];
			int stidx = lower_bound(mp[ele].begin(), mp[ele].end(), left) - 
					mp[ele].begin();
			int enidx = upper_bound(mp[ele].begin(), mp[ele].end(), right) - 
					mp[ele].begin();

			if((enidx - stidx) >= threshold) return arr[randIdx];
		}
		return -1;
	}

private:
	vector<int> arr;
	unordered_map<int, vector<int> > mp;
};

int main()
{
		
}

