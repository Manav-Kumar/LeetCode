#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>



vi shortestAlternatingPaths(int n, vvi &red_edges,vvi &blue_edges){

	vvi adjRed(n, vi()), adjBlue(n, vi());
	for(vi &r: red_edges) adjRed[r[0]].push_back(r[1]);
	for(vi &b: blue_edges) adjBlue[b[0]].push_back(b[1]);


	vector<pair<bool,int> > visitedRed(n, {false, INT_MAX});
	vector<pair<bool,int> > visitedBlue(n, {false, INT_MAX});
	int count = 0;

	priority_queue<vector<int>, vector<vector<int> >, greater<vector<int> > > pq;
	vi answer(n, -1);
	pq.push({0, 0, 0});
	pq.push({0, 0, 1});//	dst, st, color(0->red, 1->blue)
	//visitedRed[0] = {true, 0}, visitedBlue[0] = {true, 0};
	while(!pq.empty() && count < n){
		vi curr = pq.top(); pq.pop();
		int dst = curr[0], st = curr[1], color = curr[2];
		if(answer[st] == -1) answer[st] = dst, count++;

		if(color == 0){
			visitedRed[st] = {true, dst};
			for(int next: adjBlue[st]){
				if(!visitedBlue[next].first && (dst + 1) < visitedBlue[next].second){
					visitedBlue[next].second = dst + 1,pq.push({dst + 1, next, 1});
				}
			}
		}
		else if(color == 1){
			visitedBlue[st] = {true, dst};
			for(int &next: adjRed[st]){
				if(!visitedRed[next].first && (dst + 1) < visitedRed[next].second){
					visitedRed[next].second = dst + 1, pq.push({dst + 1, next, 0});
				}
			}
		}
	}
	return answer;

}

int main(){
	int n, m, s;
	cin >> n >> m >> s;
	vvi red_edges(m, vi(2)), blue_edges(s, vi(2));
	for(vi &a: red_edges) cin >> a[0] >> a[1];
	for(vi &a: blue_edges) cin >> a[0] >> a[1];
	vi answer = shortestAlternatingPaths(n, red_edges, blue_edges);
	for(int &a: answer) cout << a << " ";
	return 0;
}





