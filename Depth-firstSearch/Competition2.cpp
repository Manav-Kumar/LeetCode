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
#include <algorithm>
#include <climits>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vi >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>

vector<int> ans;

int CountApartments(int n,int v = 3){
	if(v > 7){
		return n == 0;
	}

	int ct = 0;
	while(ct*v <= n){
		bool check = CountApartments(n - ct*v, v + 2);
		if(check){
			ans[v - 3] = ct;
			return check;
		}
		ct++;
	}
	return false;
}


int Barrels(vector<ll> &arr,int k,ll maxDiff){
	priority_queue<ll> pq;
	bool check = false;
	for(ll &a: arr){
		if(maxDiff == a && !check) check = true;
		else pq.push(a);
	}

	while(!pq.empty() && k--){
		ll t = pq.top(); pq.pop();
		if(t == 0) return int(maxDiff);
		maxDiff += t;
	}
	return int(maxDiff);
}

vector<pair<int,int> >  numberOnWhiteBoard(int n){
	double curr = n, ct = n;
	n--;
	vector<pair<int,int> > ans;
	while(ct > 1){
		ans.push_back({n, curr});
		curr = (curr + n)/2;
		curr = round(curr);
		ct--, n--;
	}
	cout << curr << "\n";
	return ans;
}


int Reversal(string s){
	string t = s;
	int i = 0, j = t.size() - 1, count = 0;
	while(i < j){
		if(t[i] == t[j]){
			i++, j--;
			continue;
		}
		char ci = t[i], cj = t[j];
		int k = i;
		k = j;
		while(t[k] != ci) k--;
		while(k < j){
			swap(t[k], t[k + 1]);
			k++, count++;
		}
		k = i;
		while(t[k] != cj) k++;
		while(k > i){
			swap(t[k], t[k-1]);
			k--, count++;
		}
		
		i++, j--;
	}

	return count;
}

int main(){
	// int t, n, k;
	// cin >> t;
	// while(t--){
	// 	cin >> n >> k;
	// 	vector<ll> arr(n, 0);
	// 	ll maxDiff = 0;
	// 	for(ll &a: arr){
	// 		cin >> a;
	// 		maxDiff = max(maxDiff, a);
	// 	}
	// 	if(n == 1 || maxDiff == 0) cout << 0 << "\n";
	// 	else cout << Barrels(arr, k, maxDiff) << "\n";
	// }
	int n;
	string s;
	cin >> n >> s;
	cout << Reversal(s) << "\n";
	return 0;
}


