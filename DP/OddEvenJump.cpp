#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <cmath>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vmp vector<map<int,int> >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvmp vector<vmp>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define ll long long

ll mod = 1e9 + 7;


int oddEvenJumps(vi &A){
	int count = 0, n = A.size();
	vector<pair<bool,bool> > dp(n, pair<bool,bool> (false, false));
	dp[n-1] = pair<bool,bool> (true, true);//	Odd Even
	count += 1;
	for(int i = n-2;i >= 0;i--){
		int oddIdx = -1, oddValue = INT_MAX, evenIdx = -1, evenValue = -1;
		for(int j = i + 1;j < n;j++){
			//	Odd Value Check
			if(A[i] <= A[j] && oddValue > A[j]){
				oddValue = A[j];
				oddIdx = j;
			}

			//	Even Value Check
			if(A[i] >= A[j] && evenValue < A[j]){
				evenValue = A[j];
				evenIdx = j;
			}
		}

		if(oddIdx != -1){
			dp[i].first = dp[oddIdx].second;
		}
		if(evenIdx != -1){
			dp[i].second = dp[evenIdx].first;
		}

		if(dp[i].first) count++;

	}
	return count;
}


int oddEvenJumps2(vi &A)
{
	int count = 0, n = A.size();
	map<int,int> mp;
	vector<pair<bool,bool> > dp(n, pair<bool,bool> (false, false));
	dp[n-1] = pair<bool,bool> (true, true);//	Odd Even
	mp[A[n-1]] = n-1;
	count += 1;
	for(int i = n-2;i >= 0;i--){
		int oddIdx = -1, evenIdx = -1;

		auto it = mp.lower_bound(A[i]);
		if(it != mp.end()){
			oddIdx = it->second;
		}

		if(it != mp.end() && it->first == A[i]) evenIdx = it->second;
		else if(it != mp.begin()){
			it--;
			evenIdx = it->second;
		}

		if(oddIdx != -1){
			dp[i].first = dp[oddIdx].second;
		}
		if(evenIdx != -1){
			dp[i].second = dp[evenIdx].first;
		}

		if(dp[i].first) count++;
		mp[A[i]] = i;

	}
	return count;
}

int main(){
	int n;
	cin >> n;
	vi A(n);
	for(int &a: A) cin >> a;
	cout << oddEvenJumps2(A) << "\n";
	return 0;
}

