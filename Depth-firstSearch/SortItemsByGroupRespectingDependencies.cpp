#include <iostream>
#include <vector>
#include <queue>
#include <map>
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


vi ans;
vvi adj;
vi parent;
vb visited;

void dfs(int idx,vi &groups, int gpId,int &count,int &counter){

	if(groups[idx] != gpId && groups[idx] != -1){
		parent[idx] = -1;
		return;
	}

	visited[idx] = true;
	ans[counter++] = idx;
	count++;
	for(int &next: adj[idx]){
		if(visited[next]) continue;
		dfs(next, groups, gpId, count, counter);
	}
}



// vi sortItems(int n,int m, vi &groups, vvi &beforeItems){

// 	ans.resize(n, -1), parent.resize(n, -1), adj.resize(n), visited.resize(n, false);
// 	int counter = 0;
// 	unordered_map<int,int> mp;
// 	vb independent(n, true);
// 	rep(i, 0, n){
// 		if(groups[i] == -1) continue;
// 		mp[groups[i]] += 1;
// 	}

// 	for(int i = 0;i < n;i++)
// 	{
// 		for(int &a: beforeItems[i]){
// 			adj[a].push_back(i);
// 		}
// 	}

// 	while(1)
// 	{
// 		bool check = true;
// 		for(int i = 0;i < n;i++)
// 		{
// 			if(counter == n) break;
// 			if(!visited[i] && parent[i] == -1){
// 				check = false;
// 				int count = 0;
// 				dfs(i, groups, groups[i], count, counter);
// 				cout << groups[i] << " " << count << " " << mp[groups[i]] << "\n";
// 				if(count != mp[groups[i]]) return vi();
// 			}

// 			if(check){
// 				for(int i=0;i<n;i++) if(!visited[i] && )
// 			}
// 			if(counter == n) break;
// 		}
// 		if(counter == n) break;
// 	}

// 	return ans;
// }


vi bfs(queue<int> q, vvi &out_edges, vi &in_deg)
{
	int n = in_deg.size();
	vi ans;
	while(!q.empty()){
		int node = q.front(); q.pop();
		ans.push_back(node);
		for(int &next: out_edges[node]){
			in_deg[next] -= 1;
			if(in_deg[next] < 0) return vi();//	Means there is a cycle
			if(in_deg[next] == 0) q.push(next);
		}
	}
	return ans;
}

vi topoSort(vvi &adj){
	int n = adj.size();
	vi in_deg(n, 0);
	vb visited(n, false);
	for(vi &a: adj){
		for(int &b: a) in_deg[b] += 1;
	}
	vi start, ans;
	rep(i, 0, n){
		if(in_deg[i] == 0) start.push_back(i);
	}
	for(int &s: start){
		queue<int> q;
		q.push(s);
		vi temp = bfs(q, adj, in_deg);
		for(int &t: temp) ans.push_back(t);
	}
	return ans;
}


vi sortItems(int n,int m, vi &groups, vvi &beforeItems){

	//	Creating dummy nodes for heads and tail of each group
	vi heads(m), tails(m);
	vvi newConnections(beforeItems.size());
	for(int i = 0;i < m;i++){
		heads[i] = n + 2*i;
		tails[i] = n + 2*i + 1;
		newConnections.push_back(vi());
		newConnections.push_back(vi());
	}

	for(int item = 0;item < n;item++){

		if(groups[item] != -1){
			int head_id = heads[groups[item]], tail_id = tails[groups[item]];
			newConnections[head_id].push_back(item);
			newConnections[item].push_back(tail_id);
		}
	}

	for(int item = 0;item < n;item++){

		for(int &next: beforeItems[item]){


			if(groups[next] != groups[item]){

				int tail_id = groups[next] == -1? next: tails[groups[next]];
				int head_id = groups[item] == -1? item: heads[groups[item]];
				newConnections[tail_id].push_back(head_id);
			}
			else newConnections[next].push_back(item);

		}
	}


	vi ans = topoSort(newConnections);
	vi finalAns;
	for(int &a: ans) if(a < n) finalAns.push_back(a);

	return finalAns.size() == n? finalAns: vi();
}

//	Code has been referred from
//	https://www.youtube.com/watch?v=I4Vwkq7e2xE
//	Must watch to understand it.

int main(){
	int n,m, t;
	cin >> n >> m;
	vi groups(n);
	for(int &a: groups) cin >> a;
	vvi beforeItems(n);
	for(vi &a: beforeItems){
		cin >> t;
		a.resize(t);
		for(int &b: a) cin >> b;
	}
	vi ans = sortItems(n, m, groups, beforeItems);
	for(int &a: ans) cout << a << " ";
	return 0;
}


