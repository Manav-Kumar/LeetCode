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

double getEuclideanDst(vi &a, vi b = vi(2,0) ){
	return sqrt((double)pow(a[0] - b[0],2) + (double)pow(a[1] - b[1],2) );
}


vvi KClosest(vvi &points, int k){
	priority_queue<pair<double, vi>, vector<pair<double, vi> >, greater< pair<double,vi> > > pq;
	for(vi &a: points){
		pq.push(pair<double,vi> (getEuclideanDst(a), a ) );
	}
	vvi ans;
	while(k--){
		ans.push_back(pq.top().second);
		pq.pop();
	}
	return ans;
}

//	Diivide Conquer


vvi KClosest2(vvi &points, int k,int st,int en){

	if(st == en) return vvi (1, points[st]);

	int mid = (st + en)/2;

	vvi a1 = KClosest2(points, k, st, mid);
	vvi a2 = KClosest2(points, k, mid + 1, en);


	vvi ans;
	int i = 0, j = 0, ct = 0;
	while(ct < k){
		if(i < a1.size() && j < a2.size()){
			if(getEuclideanDst(a1[i]) <= getEuclideanDst(a2[j])) ans.push_back(a1[i++]);
			else ans.push_back(a2[j++]);
		}
		else if(i < a1.size()) ans.push_back(a1[i++]);
		else if(j < a2.size()) ans.push_back(a2[j++]);
		else break;
		ct++;
	}
	return ans;
}


int main(){
	int n, k;
	cin >> n >> k;
	vvi points(n, vi(2));
	for(vi &a: points) cin >> a[0] >> a[1];
	vvi ans = KClosest2(points, k, 0, n - 1);
	for(vi &a: ans) cout << a[0] << " " << a[1] << "\n";
	return 0;
}




