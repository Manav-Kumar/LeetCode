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


int countServers(vvi &grid){
	int n = grid.size(), m = grid[0].size();
	vi Rows(n, 0), Cols(m, 0);
	rep(i, 0, n){
		rep(j, 0, m){
			if(grid[i][j]) Rows[i] += 1, Cols[j] += 1;
		}
	}
	int count = 0;
	rep(i, 0, n) rep(j, 0, m) if(grid[i][j] && (Rows[i] > 1 || Cols[j] > 1)) count++;
	return count;
}


bool canReach(vi &arr,int start){
	int n = arr.size();
	vb visited(n, false);
	queue<int> pending;
	pending.push(start);
	visited[start] = true;
	while(!pending.empty()){
		int node = pending.front(); pending.pop();
		if(arr[node] == 0) return true;
		int left = node - arr[node], right = node + arr[node];
		if(left >= 0 && !visited[left]) visited[left] = true, pending.push(left);
		if(right < n && !visited[right]) visited[right] = true, pending.push(right);
	}
	return false;
}


//	Find eventual Safe States
void getEventualStates(vvi &graph, vi &visited,vi &ans, int idx){

	if(visited[idx] == 1){
		ans[idx] = 0;
		return ;
	}
	if(visited[idx] == 2) return ;

	visited[idx] = 1;//	Start Processing
	for(int &next: graph[idx]){
		getEventualStates(graph, visited, ans, next);
		if(ans[next] == 0) ans[idx] = 0;
	}
	visited[idx] = 2;//	End Processing
}

vi eventualSafeNodes(vvi &graph){
	int n = graph.size();
	vi visited(n, 0), ans(n, 1);
	for(int i = 0;i < n;i++){
		if(!visited[i]) getEventualStates(graph, visited, ans,  i);
	}
	vi finalAns;
	for(int i = 0;i < n;i++) if(ans[i]) finalAns.push_back(i);
	return finalAns;
}

//	Reconstruct Iternary
//	Here we need to visit each and every edge once and has nothing to talk about the vertices

bool helper(vvi &edges,vb &visited, int idx,vi &sol, int count = 0){

	int m = edges.size();
	if(count == m) return true;

	priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > indexes;
	for(int i = 0;i < m;i++){
		if(visited[i] || edges[i][0] != idx) continue;
		indexes.push({edges[i][1], i} );
	}

	while(!indexes.empty()){
		int i = indexes.top().second, next = indexes.top().first;
		indexes.pop();
		visited[i] = true;
		sol.push_back(next);
		bool ans = helper(edges, visited, next, sol, count + 1);
		if(ans) return true;
		sol.pop_back();
		visited[i] = false;
	}

	return false; 
}


vector<string> findItinerary(vvs &tickets){
	set<string> city;
	for(vs &a: tickets) city.insert(a[0]), city.insert(a[1]);
	map<string,int> mp;
	map<int,string> remp;
	int n = 0, m = tickets.size(), start = -1;
	for(auto it = city.begin();it != city.end();it++){
		if(*it == "JFK") start = n;
		mp[*it] = n, remp[n++] = *it;
	}
	vvi edges;
	for(vs &s: tickets) edges.push_back({mp[s[0]], mp[s[1]] } );
	vb visited(edges.size(), false);
	vi sol;
	sol.push_back(start);
	bool ans = helper(edges, visited, start, sol);
	vs finalAns;
	for(int &a: sol) finalAns.push_back(remp[a]);
	return finalAns;
}



bool compare(vi &a, vi &b){
	if(a[0] == b[0]) return a[1] < b[1];
	return a[0] < b[0];
}


bool helper2(vvi &edges,vb &visited, int idx,vi &sol, int count = 0){

	int m = edges.size();
	if(count == m) return true;

	int st = 0, en = m - 1, start = -1;
	while(st <= en){
		int mid = (st + en)/2;
		if(edges[mid][0] > idx) en = mid - 1;
		else if(edges[mid][0] < idx) st = mid + 1;
		else if(edges[mid][0] == idx){
			start = mid;
			en = mid - 1;
		}
	}
	if(start < 0) return false;

	for(;start < m && edges[start][0] == idx;start++){
		if(visited[start]) continue;
		visited[start] = true;
		sol.push_back(edges[start][1]);
		bool ans = helper2(edges, visited, edges[start][1], sol, count + 1);
		if(ans) return true;
		sol.pop_back();
		visited[start] = false;
	}

	return false; 
}

vs findItinerary2(vvs &tickets){
	set<string> city;
	for(vs &a: tickets) city.insert(a[0]), city.insert(a[1]);
	map<string,int> mp;
	map<int,string> remp;
	int n = 0, m = tickets.size(), start = -1;
	for(auto it = city.begin();it != city.end();it++){
		if(*it == "JFK") start = n;
		mp[*it] = n, remp[n++] = *it;
	}
	vvi edges;
	for(vs &s: tickets) edges.push_back({mp[s[0]], mp[s[1]] } );
	sort(edges.begin(), edges.end(), compare);
	vb visited(edges.size(), false);
	vi sol;
	sol.push_back(start);
	bool ans = helper2(edges, visited, start, sol);
	vs finalAns;
	for(int &a: sol) finalAns.push_back(remp[a]);
	return finalAns;
}

bool compare2(vs &a, vs &b){
	if(a[0] == b[0]) return a[1] < b[1];
	return a[0] < b[0];
}

bool helper3(vvs &tickets,vb &visited,vs &sol, string idx = "JFK",int count = 0){
	int m = tickets.size();
	if(m == count)return true;

	int st = 0, en = m - 1, start = -1;
	while(st <= en){
		int mid = (st + en)/2;
		if(tickets[mid][0] > idx) en = mid - 1;
		else if(tickets[mid][0] < idx) st = mid + 1;
		else if(tickets[mid][0] == idx){
			start = mid;
			en = mid - 1;
		}
	}
	if(start < 0) return false;

	for(;start < m && tickets[start][0] == idx;start++){
		if(visited[start]) continue;
		visited[start] = true;
		sol.push_back(tickets[start][1]);
		bool ans = helper3(tickets, visited, sol, tickets[start][1], count + 1);
		if(ans) return true;
		sol.pop_back();
		visited[start] = false;
	}

	return false;
}

vs findItinerary3(vvs &tickets){
	sort(tickets.begin(), tickets.end(), compare2);
	int m = tickets.size();
	vb visited(m, false);
	vs sol;
	sol.push_back("JFK");
	bool check = helper3(tickets, visited, sol);
	return sol;
}

int main(){
	int n, t;
	cin >> n;
	vvs tickets(n, vs(2));
	for(vs &a: tickets){
		cin >> a[0] >> a[1];
	}
	vs ans = findItinerary2(tickets);
	for(string &a: ans) cout << a << " ";

	return 0;
}




