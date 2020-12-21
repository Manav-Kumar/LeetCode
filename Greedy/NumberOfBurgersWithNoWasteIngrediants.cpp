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
#define vll vector<ll>
#define vi vector<int>
#define vvi vector<vi >
#define vvvi vector<vvi>
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>


vi numOfBurgers(int tomatoSlices, int cheeseSlices){
	if(tomatoSlices%2) return vi();
	int c1 = 0, c2 = 0, t = tomatoSlices - 2*cheeseSlices;
	if(t < 0 || t%2) return vi();
	c1 = t/2, c2 = cheeseSlices - c1;
	if(c2 < 0) return vi();
	cout << c1 << " " << c2 << "\n";
	return vi{c1, c2};
}

//	Reconstruct a 2-Row Binary Matrix
vvi reconstructMatrix(int upper,int lower,vi &colsum){
	int n = colsum.size();
    vvi ans(2, vi(n, 0));
    rep(i, 0, n){
        if(colsum[i] == 0) ans[0][i] = 0, ans[1][i] = 0;
        else if(colsum[i] == 2) ans[0][i] = 1, ans[1][i] = 1, lower--, upper--;
    }
    rep(i, 0, n){
        if(colsum[i] == 1){
            if(upper > lower) ans[0][i] = 1, upper--;
            else ans[1][i] = 1, lower--;
        }
    }
    if(upper != 0 || lower != 0) return vvi();
    return ans;
}

//	Largest Values From Intervals
bool comp(vi &a, vi &b){
	return a[0] > b[0];
}

int largestValsFromLabels(vi &values, vi &labels, int num_wanted, int use_limit){
	int n = values.size(), ans = 0, totalct = 0;
	vvi arr;
	rep(i, 0, n) arr.push_back({values[i], labels[i]});
	sort(arr.begin(), arr.end(), comp);
	map<int,int> labmp;
	rep(i, 0, n){
		int v = arr[i][0], l = arr[i][1];
		if(labmp[l] < use_limit){
			ans += v, labmp[l] += 1, totalct += 1;
		}
		if(totalct == num_wanted) return ans;
	}
	return ans;
}


int main(){
	return 0;
}





