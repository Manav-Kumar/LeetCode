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


int minKBitFlips(vi &A, int k){
	int ans = 0, n = A.size(), count = 0;
	queue<int> s;
	for(int i = 0;i < n;i++){

		if(!s.empty() && s.front() == i){
			count--;
			s.pop();
		}

		if(count%2 != 0) A[i] ^= 1;

		if(A[i] == 0){
			if(i + k > n) return -1;
			A[i] ^= 1, count++;
			s.push(i + k);
			ans++;
		}

	}
	return ans;
}


int main(){
	int n, k;
	cin >> n >> k;
	vi A(n);
	for(int &a: A) cin >> a;
	cout << minKBitFlips(A, k) << "\n";
	return 0;
}








