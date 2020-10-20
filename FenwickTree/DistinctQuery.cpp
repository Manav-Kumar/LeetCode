#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

#define MAX 1000000

void update(int *BIT,int idx,int n,int value){

	for(;idx <= n;idx += (idx&(-idx))){
		BIT[idx] += value;
	}
}

int query(int *BIT,int idx){
	int sum = 0;
	for(;idx > 0;idx -= (idx&(-idx))){
		sum += BIT[idx];
	}
	return sum;
}

class node{
public:
	int f,s, index;
};

bool compare(node &a,node &b){
	if(a.s == b.s) return a.f < b.f;
	return a.s < b.s;
}

int main(){
	int n, q, i, j;
	cin >> n;
	int *arr = new int[n+1];
	int *BIT = new int[n+1]();
	for(int i=1;i<=n;i++){
		cin >> arr[i];
	}
	cin >> q;
	node *questions = new node[q];
	for(int i=0;i<q;i++){
		cin >> questions[i].f >> questions[i].s;
		questions[i].index = i;
	}
	sort(questions, questions + q, compare);
	map<int,int> visited;
	int *ans = new int[q];
	int idx = 1;
	for(int i = 0;i < q;i++){
		node temp = questions[i];
		while(idx <= temp.s){

			if(visited.find(arr[idx]) != visited.end()){
				update(BIT, visited[arr[idx]], n, -1);
			}
			visited[arr[idx]] = idx;
			update(BIT, idx, n, 1);
			idx++;
		}
		ans[temp.index] = query(BIT, temp.s) - query(BIT, temp.f - 1);
	}
	for(int i=0;i<q;i++) cout << ans[i] << "\n";

	delete []ans;
	delete []BIT;
	delete []arr;
	return 0;
}


