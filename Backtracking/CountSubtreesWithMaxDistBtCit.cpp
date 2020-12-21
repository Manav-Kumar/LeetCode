#include<iostream>
#include <vector>
#include <queue>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>


pair<int,int> dfs(vvi &adj, int &mask, int start,int parent = -1){

	mask ^= (1<<start);
	pair<int,int> ans(0, 0);
	int fmxht = 0, smxht = 0;
	for(int &next: adj[start]){
		if((mask&(1<<next)) == 0 || next == parent) continue;
		pair<int,int> smallAns = dfs(adj, mask, next, start);
		smallAns.first += 1;

		ans.first = max(ans.first, smallAns.first);
		ans.second = max(ans.second, smallAns.second);//	Update the diameter

		if(fmxht < smallAns.first) smxht = fmxht, fmxht = smallAns.first;
		else if(smxht < smallAns.first) smxht = smallAns.first;
	}

	ans.second = max(ans.second, fmxht + smxht);

	return ans;
}


int BFS(vvi &adj,int mask){
	int d = -1, n = adj.size(), curr = 0, currMask;
	queue<int> q;
	for(int i = 0;i<n;i++){
		if((mask&(1<<i)) == 0) continue;
		currMask = mask, curr = 0;
		queue<int> q;
		q.push(i);

		while(q.size() > 0){
			int sz = q.size();
			while(sz--){
				int t = q.front(); q.pop();
				currMask ^= (1<<t);
				for(int &next: adj[t]){
					if((currMask&(1<<next))) q.push(next);
				}
			}
			curr++;
		}

		if(currMask == 0){
			d = max(curr - 1, d);
		}
	}
	return d;
}

vector<int> CountSubGraphOfEachDia(int n,vvi &edges){
	vi ans(n-1, 0);
	vvi adj(n, vi());
	for(vi &a: edges){
		adj[a[0] - 1].push_back(a[1] - 1);
		adj[a[1] - 1].push_back(a[0] - 1);
	}

	for(int i = 1;i < (1<<n);i++){
		if((i&(i-1)) == 0) continue;//	If single element is there ignore it.
		int mask = i, maxDst = 0, u = -1;
		for(int j=0;j < n;j++){
			if(mask&(1<<j)){
				u = j; break;
			}
		}
		int d = BFS(adj, mask);
		if(d != -1){
			ans[d - 1] += 1;
		}
		// pair<int,int> a = dfs(adj, mask, u);
		// if(mask == 0) ans[a.second - 1] += 1;

	}
	return ans;
}

int main(){
	int n;
	cin >> n;
	vvi edges(n - 1,vi(2));
	for(vi &a: edges){
		cin >> a[0] >> a[1];
	}
	vi ans = CountSubGraphOfEachDia(n, edges);
	for(int &a: ans) cout << a << " ";
	cout << "\n";
	return 0;
}


