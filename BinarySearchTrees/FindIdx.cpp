#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>

bool compare(pair<int,int> &a, pair<int,int> &b){
	if(a.first == b.first) return a.second < b.second;
	return a.first < b.first;
}

vector<int> solve(vector<int> a,vector<int> b){

	vector<pair<int,int> > arr;
	for(int i=0;i<b.size();i++) arr.push_back({b[i], i});

	sort(arr.begin(), arr.end(), compare);
	
	int n = a.size(), q = b.size();
	vector<int> sol(q, -1);
	int i = 0, j = 0;

	while(i < q){
		if(j == n) return sol;
		if(a[j] >= arr[i].first) sol[arr[i++].second] = j;
		else j++;
	}
	return sol;
}


//	Maximize the Matrix
pair<int,int> getMinIdx(vector<vector<int> > a){
	int n = a.size(), m = a[0].size(), value = 1e8 + 9;
	pair<int,int> ans(-1,-1);
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(value > a[i][j]) ans = {i, j}, value = a[i][j];
		}
	}
	return ans;
}
int solve2(vector<vector<int> > A,int B,int C){
	int n = A.size(), m = A[0].size();
	while(B--){
		pair<int,int> idx = getMinIdx(A);
		int i = idx.first, j = idx.second, sminvalue = 1e8 + 9, dir = 0;//	0->left, 1->right
		for(int ct = 0;ct < C-1 && j - ct - 1 >= 0;ct++){
			if(sminvalue > A[i][j - ct - 1]) sminvalue = A[i][j - ct - 1];
		}
		for(int ct = 0;ct < C-1 && j + ct + 1 < m;ct++){
			if(sminvalue > A[i][j + ct + 1]) sminvalue = A[i][j + ct + 1], dir = 1;
		}
	}
	
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<int> a(n), b(m);
	for(int &c: a) cin >> c;
	for(int &c: b) cin >> c;
	vector<int> ans = solve(a, b);
	for(int c: ans) cout << c << " ";
	return 0;
}