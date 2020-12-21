#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>

typedef long long ll;

ll mod = 1e6 + 3;

class comparator{
public:
	bool operator() (vi &a, vi &b){
		return a[0] + a[2] > b[0] + b[2];
	}
};

int MinTimeToRecover(int n, vector<int> &expertise){
	priority_queue<vi , vector<vi >, comparator > pq;
	for(int &k: expertise) pq.push({0, k, 1*k});
	int ans = 0;
	while(n--){

		vi curr = pq.top(); pq.pop();

		curr[0] += curr[2], curr[2] += curr[1];
		ans = max(ans, curr[0]);

		pq.push(curr);
	}
	return ans;
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<int> expertise(m);
	for(int &a: expertise) cin >> a;
	cout << MinTimeToRecover(n, expertise) << "\n";
	return 0;	
}





