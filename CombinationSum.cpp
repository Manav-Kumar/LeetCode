#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_map>

using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define rep(i,a,b) for(int i=a;i<b;i++)

void helper(vi& candidates,int target,vvi &ret,vi& ans,int idx = 0)
{
	if(target == 0 || idx == candidates.size())
    {
        if(target == 0) ret.push_back(ans);
        return;
    }
    int count = 0;
    while(1)
    {
        if(count*candidates[idx] > target) break;
        if(count) ans.push_back(candidates[idx]);
        helper(candidates, target - count*candidates[idx], ret, ans, idx+1);
        count++;
    }
    count--;
    while(count)
    {
    	ans.pop_back();
    	count--;   
    }
}

vvi combinationSum(vi& candidates, int target)
{
	vvi ret;
	vi ans;
	helper(candidates, target, ret, ans);
	return ret;
}


// Each candidate number may be used only once to make sum target
void helper2(unordered_map<int,int>& mp, int target,vector<int> &ans, 
				vector<vector<int> >& ret,unordered_map<int,int>::iterator it)
{
	if(target == 0)
	{
		ret.push_back(ans);
		return;
	}
	if(it == mp.end()) return;
	int i = 0;
	for(;i <= it->second;i++)
	{
		if(target < (i*it->first)) break;
		if(i!=0) ans.push_back(it->first);
		helper(mp, target - (i*it->first), ans, ret, next(it));
	}
	i--;
	while(i > 0) 
	{
		ans.pop_back();
		i--;
	}
}

vector<vector<int> > combinationSum2(vector<int> &candidates, int target)
{
	unordered_map<int,int> mp;
	for(int c: candidates) mp[c] += 1;
	vector<vector<int> > ret;
	vector<int> ans;
	helper(mp, target, ans, ret,mp.begin());
	return ret;
}

int main()
{
	int n,target;
	cin >> n;
	vi candidates;
	candidates.resize(n);
	for(int &a: candidates) cin >> a;
	cin >> target;
	vvi ans = combinationSum(candidates, target);
	for(vi a: ans)
	{
		for(int c: a) cout << c << " ";
		cout << "\n";
	}
	return 0;
}