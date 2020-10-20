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

int n,a,b,c;

vector<int> display;

bool RLTraverse(int bl,int idx,int stop,vector<int> arr,int finalOccur, int maxOccur = 1){

	if(idx <= stop){

		if(bl == 0) display = arr;
		return bl == 0;
	}

	for(int i = maxOccur;i <= finalOccur;i++){
		arr[idx] = i;
		if(RLTraverse(bl-1, idx - 1, stop, arr, finalOccur, i)) return true;
	}

	for(int i = 1;i < maxOccur;i++){
		arr[idx] = i;
		if (RLTraverse(bl, idx - 1, stop, arr, finalOccur, maxOccur)) return true;
	}

	return false;
}


bool LRTraverse(int al,vector<int> arr, int idx = 0,int maxOccur = 1)
{
	if(al == 0){
		//Last C buildings heights should be same
		int count = 0;
		for(int i=idx-1;i>=0;i--){
			if(arr[i] == maxOccur) count++;
			else break;

		if(count != c) return false;
		return RLTraverse(b - count, n-1, idx - 1, arr, maxOccur - 1);
	}
	if(idx == n){
		return false;
	}
	for(int i=maxOccur;i <= n;i++){
		arr[idx] = i;
		if (LRTraverse(al-1, arr, idx + 1, i)) return true;
	}
	for(int i=1;i<maxOccur;i++){
		arr[idx] = i;
		if (LRTraverse(al, arr, idx + 1,maxOccur)) return true;
	}
	arr[idx] = -1;

	return false;
}

bool HighBuildings()
{
	cin >> n >> a >> b >> c;
	vector<int> arr(n, -1);
	display.resize(n);
	return LRTraverse(a, arr);
}

int main()
{
	int T;
	cin >> T;
	rep(t,1,T+1)
	{
		bool ans = HighBuildings();
		cout << "Case #" << t << ": ";
		if(!ans) cout << "IMPOSSIBLE\n";
		else{
			rep(i,0,n) cout << display[i] << " ";
			cout << "\n";
		}
	}
	return 0;
}


