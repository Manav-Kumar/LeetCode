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
#define vvl vector<vl>
#define vvll vector<vll>
#define vvb vector<vector<bool> >

void KsortedArray(vector<int> &a,int k)
{
	priority_queue<int> pq;
	int t = 0, n = a.size();
	for(int i = 0;i<k && i < n;i++) pq.push(a[i]);

	for(int i=k;i<n;i++)
	{
		a[t] = pq.top();
		pq.pop();
		pq.push(a[i]);
		t++;
	}
	while(!pq.empty())
	{
		a[t] = pq.top();
		pq.pop();
		t++;
	}
	
}

int main()
{
	int n,k;
	cin >> n >> k;
	vector<int> a(n);
	for(int &b: a) cin >> b;
	KsortedArray(a,k);
	for(int b: a) cout << b << " ";
	return 0;
}