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
#define vvi vector<vector<int> >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>



long double frogPosition(vvi &edges, int t,int target,vb &visited, int idx = 1){

	if(t == 0){
		return idx == target?1:0;
	}
	if(t < 0) return 0;
	int counter = 0;
	long double ans = 0;
	visited[idx] = true;
	for(vi &a: edges){
		double temp = 0;
		if(a[0] == idx && !visited[a[1]]){
			if(ans == 0.0) temp = frogPosition(edges, t - 1, target, visited, a[1]);
			counter++;
		}
		else if(a[1] == idx && !visited[a[0]]){
			if(ans == 0.0) temp = frogPosition(edges, t - 1, target, visited, a[0]);
			counter++;
		}

		ans = fmax(ans, temp);
	}

	if(counter == 0) return idx == target?1:0;

	return ans/counter;
}


double getAns(vi &parent,int target,vi &childCt)
{
	double ans = 1;
	while(target != -1)
	{
		ans *= (1.0/childCt[target]);
		target = parent[target];
	}
	return ans;
}

double bfs(int n, vvi &edges, int t, int target)
{
	if(target == 1){
		int ct = 0;
		for(vi &a: edges){
			if(a[0] == target){
				ct++; break;
			}
			else if(a[1] == target){
				ct++; break;
			}
		}
		return ct == 0?1:0;
	}
	queue<int> q;
	q.push(1);
	vb visited(n + 1, false);
	visited[1] = true;
	vi parent(n + 1, -1);
	vi childCt(n + 1, 0);
	while(!q.empty()){

		if(t <= 0) return 0;
		int sz = q.size();
		for(int i = 0;i < sz;i++){
			int idx = q.front(), counter = 0; q.pop();
			bool check = false;
			for(vi &a: edges){

				if(a[0] == idx && !visited[a[1]]){
					visited[a[1]] = true;
					q.push(a[1]);
					if(a[1] == target) check = true;
					parent[a[1]] = idx;
					counter++;
				}
				else if(a[1] == idx && !visited[a[0]]){
					visited[a[0]] = true;
					q.push(a[0]);
					if(a[0] == target) check = true;
					parent[a[0]] = idx;
					counter++;
				}
			}
			childCt[idx] = counter;
			if(check){
				int ct = 0;
				visited[target] = true;
				for(vi &a: edges){
					if(a[0] == target && !visited[a[1]]){
						ct++; break;
					}
					else if(a[1] == target && !visited[a[0]]){
						ct++; break;
					}
				}

				if(t == 1 || ct == 0) return getAns(parent, parent[target], childCt);
				return 0;
			}

		}
		t--;
	}

	return 0;
}

int main(){
	int n, m, t, target;
	cin >> n >> m;
	vvi edges(m, vi(2, -1));
	for(vi &a: edges) cin >> a[0] >> a[1];
	cin >> t >> target;
	vb visited(n + 1, false);
	cout << frogPosition(edges, t, target, visited) << "\n";
	cout << bfs(n, edges, t, target) << "\n";
	return 0;
}






