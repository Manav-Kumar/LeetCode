#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <unordered_map>
#include <set>
#include <iomanip>
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
#define vll vector<ll>
#define vi vector<int>
#define vvi vector<vi >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>

ll n, w;
vll initialValues;


ll MinCount2(){
	sort(initialValues.begin(), initialValues.end());
	ll ans = -1, t = 0;
	for(ll &i: initialValues){
		t = 0;
		for(ll &a: initialValues){
			if(i < a){
				t += min(a - i, n - a + i);
			}
			else if(i > a){
				t += min(i - a, a + n - i);
			}
		}
		if(ans == -1) ans = t;
		else ans = min(ans, t);
	}
	return ans;
}

int main(){
	cin >> n >> w;
	initialValues.clear(), initialValues.resize(w);
	for(ll &a: initialValues) cin >> a;
	cout << MinCount2() << "\n";
	return 0;
}


// vll totalScore;

// void MergeCards(vi A, ll score = 0){
// 	int n = A.size();
// 	if(n == 1){
// 		totalScore.push_back(score);
// 		return;
// 	}

// 	for(int i = 1;i < n;i++){
// 		vi temp;
// 		for(int j = 0;j <= i-2;j++) temp.push_back(A[j]);
// 		temp.push_back(A[i - 1] + A[i]);
// 		for(int j = i + 1;j < n;j++) temp.push_back(A[j]);
// 		MergeCards(temp, score + A[i - 1] + A[i]);
// 	}
// }


// pair<int,int> MergeCards2(vi A,int st,int en)
// {
// 	if(st >= en) return pair<int,int> (0, 1);
// 	int k = 0;
// 	for(int i = st;i <= en;i++) k += A[i];

// 	pair<int,int> ans(0,0);
// 	for(int j = st + 1;j <= en;j++){
// 		pair<int,int> a1 = MergeCards2(A, st, j - 1);
// 		pair<int,int> a2 = MergeCards2(A, j, en);

		

// 		int t = a1.first*a2.second + a2.first*a1.second + k*a1.second*a2.second;
// 		if(st == 0 && en == 3){
// 			cout << st << " " << j-1 << " " << j << " " << en << "\n";
// 			cout << a1.first << " " << a1.second << " " << a2.first << " " << a2.second << "\n";
// 			cout << "totalScore: " << t << "\n\n";
// 		}
// 		ans.first += t;
// 		ans.second += a1.second*a2.second;

// 	}
// 	return ans;
// }

// int main(){

// 	vector<double> fact(5001, 1);
// 	for(int i = 2;i <= 5000;i++) fact[i] = i*fact[i - 1];

// 	int T, n;
// 	cin >> T;
// 	rep(t, 1, T + 1){
// 		totalScore.clear();
// 		cin >> n;
// 		vi A(n);
// 		for(int &a: A) cin >> a;

// 		MergeCards(A);
		
		
// 		long double ans = 0, s = fact[n - 1];
// 		int K = 0;
// 		for(ll &a: totalScore){
// 			cout << a << " ";
// 			K += a;
// 			ans += a/s;
// 		}

// 		cout << "\n";
// 		pair<int,int> d = MergeCards2(A, 0, n - 1);

// 		cout << "\n" << K << " " << d.first << "\n";

// 		cout << "Case #" << t << ": " << setprecision(20) << ans << "\n";
// 	}

// 	return 0;
// }











