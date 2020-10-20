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

pair<int,int> helper(vvi &edges,int idx, vb &visited)
{
	int sum = 0, ct = 1;
	visited[idx] = true;
	pair<int,int> temp;
	for(vi &a: edges){
		if(idx == a[0] && !visited[a[1]]){
			temp = helper(edges, a[1], visited);
			sum += temp.first + temp.second, ct += temp.second;
		}
		else if(idx == a[1] && !visited[a[0]]){
			temp = helper(edges, a[0], visited);
			sum += temp.first + temp.second, ct += temp.second;
		}
	}
	return pair<int,int> (sum, ct);
}


vi sumOfDistancesInTree(int n,vvi &edges)
{
	vi ans(n, 0);
	rep(i, 0, n){
		vb visited(n, false);
		ans[i] = helper(edges, i, visited).first;
	}
	return ans;
}


pair<int,int> helper2(vvi &edges,int idx, vb &visited, vi &parent, vpii &subTreeSum)
{
	int sum = 0, ct = 1;
	visited[idx] = true;
	pair<int,int> temp;
	for(vi &a: edges){
		if(idx == a[0] && !visited[a[1]]){
			parent[a[1]] = idx;
			temp = helper2(edges, a[1], visited, parent, subTreeSum);
			sum += temp.first + temp.second, ct += temp.second;
		}
		else if(idx == a[1] && !visited[a[0]]){
			parent[a[0]] = idx;
			temp = helper2(edges, a[0], visited, parent, subTreeSum);
			sum += temp.first + temp.second, ct += temp.second;
		}
	}
	pair<int,int> ans(sum, ct);
	subTreeSum[idx] = ans;
	return ans;
}

int heightSum(vpii &subTreeSum,int idx,vi &parent)
{
	pair<int,int> prev = subTreeSum[idx];
	int ans = prev.first, ht = 1, temp;
	idx = parent[idx];
	while(idx != -1)
	{
		pair<int,int> curr = subTreeSum[idx];
		temp = curr.first - (prev.first + prev.second) + ht*(curr.second - prev.second);
		cout << temp << "\n";
		ans += temp;
		idx = parent[idx];
		prev = curr, ht++;
	}
	return ans;
}

vi sumOfDistancesInTree2(int n, vvi &edges)
{
	vi ans(n, 0), parent(n, -1);
	vpii subTreeSum(n);
	vb visited(n, false);
	ans[0] = helper2(edges, 0, visited, parent, subTreeSum).first;
	rep(i, 1, n)
	{
		ans[i] = heightSum(subTreeSum, i, parent);
	}
	return ans;
}

void postOrder(vi &dst,vi &count, vvi &adj,int idx,int parent)
{
	for(int &next: adj[idx])
	{
		if(next == parent) continue;
		postOrder(dst, count, adj, next, idx);

		dst[idx] += dst[next] + count[next];
		count[idx] += count[next];
	}
	count[idx] += 1;
}

void preOrder(vi &dst,vi &count, vvi &adj,int idx,int parent){

	for(int &next: adj[idx])
	{
		if(next == parent) continue;
		dst[next] = dst[idx] - count[next] + adj.size() - count[next];
		preOrder(dst, count, adj, next, idx);
	}
}

//	O(N) Solution
vi sumOfDistancesInTree3(int n, vvi &edges)
{
	vi dst(n, 0), count(n, 0);
	vvi adj(n);
	for(vi &a: edges){
		adj[a[0]].push_back(a[1]);
		adj[a[1]].push_back(a[0]);
	}
	postOrder(dst, count, adj, 0, -1);
	preOrder(dst, count, adj, 0, -1);

	return dst;
}


int main(){
	int n;
	cin >> n;
	vvi edges(n - 1, vi(2));
	for(vi &a: edges) cin >> a[0] >> a[1];
	vi ans = sumOfDistancesInTree2(n, edges);
	for(int &a: ans) cout << a << " ";
	return 0;
}


