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
#include <list>
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

void XORhelper(int &ans,vi &p, vi &a, vi temp, int OccupiedPos,vvb &visited, int currXorSum = 0,int idx = 0){
	int n = p.size();
	if(idx == n){
		int curr = temp[0]^temp[1]^temp[2], sum = curr*p[2];
		for(int i = 3;i < n;i++){
			curr ^= temp[i - 3] ^ temp[i];
			sum += curr*p[i];
		}
		ans = min(ans, sum);
		return;
	}
	// if(idx >= 4){
	// 	int k = temp[idx - 1]^temp[idx - 2]^temp[idx - 3], c = k^temp[idx - 1]^temp[idx - 4];
	// 	if (visited[OccupiedPos][currXorSum - (c*p[idx - 2] + k*p[idx - 1])]) return;
	// }
	if(currXorSum >= 200) cout << "notok";
	int k = 0;
	for(int pos = 0;pos < n;pos++){
		if((OccupiedPos>>pos)&1) continue;
		temp.push_back(a[pos]);
		if(idx >= 2){
			k = (temp[idx]^temp[idx - 1]^temp[idx - 2])*p[idx];
		}	
		if(ans > currXorSum + k) XORhelper(ans, p, a, temp, OccupiedPos | (1<<pos), visited, currXorSum + k, idx + 1);

		temp.pop_back();
	}
	//visited[OccupiedPos][currXorSum] = true;
}





int main(){
	int n, q, u, v;
	cin >> n;
	vi nodes(n, 0);
	nodes[0] = 1;
	vvi adj(n,vi());
	rep(i, 0, n-1){
		cin >> u >> v;
		u--, v--;
		adj[u].push_back(v), adj[v].push_back(u);
	}
	while(q--){
		cin >> u >> v;
		v--;
		if(u == 0){
			if(nodes[v] == 1) cout << 0 << "\n";
			else{
				
			}
		}
		else if(u == 1){

		}
	}
	return 0;
}




