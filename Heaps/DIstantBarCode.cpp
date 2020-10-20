#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <unordered_map>
#include <set>
#include <cmath>
#include <math.h>
#include <unordered_set>
#include <deque>
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
#define vs vector<string>
#define vvc vector<vc>
#define vvi vector<vector<int> >
#define vvvi vector<vvi>
#define vvl vector<vl>
#define vvll vector<vll>
#define vvb vector<vector<bool> >
#define vvvb vector<vvb>

class comparator{
public:
	bool operator()(const pair<int,int> &a,const pair<int,int> &b){
		return a.second < b.second;
	}
};

vector<int> rearrangeBarcodes(vector<int> &barcodes)
{
	vector<int> ans;
	priority_queue<pair<int,int>, vector<pair<int,int> >, comparator> q;
	map<int,int> mp;
	for(int &a: barcodes) mp[a]++;
	pair<int,int> t1, t2;
	for(auto it = mp.begin();it != mp.end();it++){
		q.push(pair<int,int> (it->first, it->second));
	}
	while(q.size() > 1){
		t1 = q.top();
		q.pop();
		t2 = q.top();
		q.pop();
		ans.push_back(t1.first);
		ans.push_back(t2.first);
		t1.second--, t2.second--;
		if(t1.second > 0) q.push(t1);
		if(t2.second > 0) q.push(t2);
	}
	if(!q.empty()) ans.push_back(q.top().first);
	return ans;
}

//	Split The Array Into Consecutive Subsequences

bool isPossible(vi &nums)
{
	int n = nums.size();
	unordered_map<int,int> freq;
	for(int &a: nums) freq[a]++;

	// ending[x] tells how many subequences are there ending at x
	unordered_map<int,int> ending;
	for(int &a: nums){
		int ct = freq[a];
		if(ct == 0) continue;
		if(ending[a-1] >= ct){
			ending[a] += ct;
		}
		else{
			ending[a] += ending[a - 1];
			ct -= ending[a - 1];
			if(freq[a + 1] >= ct && freq[a + 2] >= ct){
				//To make sure it's least size becomes 3
				freq[a + 1] -= ct;
				freq[a + 2] -= ct;
				ending[a + 2] += ct;
			}
			else return false;
		}
		freq[a] = 0;
	}
	return true;
}


int main()
{
	int n;
	cin >> n;
	vector<int> barcodes(n);
	for(int &a: barcodes) cin >> a;
	vector<int> ans = rearrangeBarcodes(barcodes);
	for(int &a: ans) cout << a << " ";
	return 0;
}

