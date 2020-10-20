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
#include <algorithm>
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


bool helper(vi &leftChild,vi &rightChild,vi &parent,int &count,int idx, int pt = -1){

	if(parent[idx] != -2) return false;
	parent[idx] = pt, count++;
	bool check = true;
	if(leftChild[idx] != -1) check = helper(leftChild, rightChild, parent, count, leftChild[idx], idx);
	if(!check) return check;
	if(rightChild[idx] != -1) check = helper(leftChild, rightChild, parent, count, rightChild[idx], idx);
	return check;
}


bool validateBinaryTreeNodes(int n, vi &leftChild, vi &rightChild){
	vi parent(n, -2);
	int count = 0, idx = -1;
	vb start(n, true);
	for(int i = 0;i < n;i++){
		if(leftChild[i] != -1) start[leftChild[i]] = false;
		if(rightChild[i] != -1) start[rightChild[i]] = false;
	}
	for(int i = 0;i < n;i++){
		if(start[i]){
			if(idx != -1) return false;
			idx = i;
		}
	}
	if(idx == -1) return false;
	return helper(leftChild, rightChild, parent, count, idx);

}


//	Keys And Rooms
void helper2(vvi &rooms,vb &visited,int &count, int idx = 0){

	visited[idx] = true;
	count++;
	for(int &next: rooms[idx]){
		if(!visited[next]) helper2(rooms, visited, count, next);
	}
}

bool canVisitAllRooms(vvi &rooms){
	int n = rooms.size();
	vb visited(n, false);
	int count = 0;
	helper2(rooms, visited, count);
	return count == n;
}

//	Couples Holding Hands
int minSwapsCouples(vi &row,map<int,int> &remp, int start){
    if(start >= row.size()) return 0;
    
    int v1 = row[start], v2 = v1%2 == 0?(v1 + 1):(v1 - 1);
    int j = remp[v2];
    remp[v2] = remp[row[start + 1]];
    remp[row[start + 1]] = j;
    swap(row[start + 1], row[j]);
    int ans = minSwapsCouples(row,remp, start + 2) + ((start + 1) == j?0:1);
    return ans;
}

int minSwapsCouples(vi &row){
 	map<int,int> remp;
    for(int i = 0;i < row.size();i++) remp[row[i]] = i;
    return minSwapsCouples(row,remp, 0);
}


//	K Similar Strings
int kSimilarity(string a,string b,unordered_map<string,int> &visited, int ia = 0,int ib = 0){
        
    string s = a.substr(ia); 
    if(visited.count(s) > 0) return visited[s];
    if(ia == a.size()) return 0;
    if(a[ia] == b[ib]) return kSimilarity(a, b, visited, ia + 1, ib + 1);
    int ans = INT_MAX;
    for(int i = ia + 1;i < a.size();i++){
        if(a[i] == b[ib]){
            swap(a[ia], a[i]);
            ans = min(ans, kSimilarity(a, b, visited, ia + 1, ib + 1) + 1);
            swap(a[ia], a[i]);
        }
    }
    visited[s] = ans;
    return ans;
}

//	BFS Approach
int kSimilarity(string a,string b){

	unordered_set<string> visited;
	queue<pair<string,string> > pending;
	pending.push({a, b});
	int count = 0;
	while(!pending.empty()){
		int sz = pending.size();
		while(sz--){
			string a = pending.front().first, b = pending.front().second;
			pending.pop();
			if(a.empty()) return count;
			int idx = 0;
			while(idx < a.size() && a[idx] == b[idx]) idx++;
			if(idx == a.size()) return count;
			a = a.substr(idx), b = b.substr(idx);
			for(int i = 0;i < a.size();i++){
				if(a[i] == b[0]){
					swap(a[0], a[i]);
					if(visited.count(a) == 0) pending.push({a.substr(1), b.substr(1)});//Insert at next level
					visited.insert(a);
					swap(a[0], a[i]);
				}
			}


		}

		count++;
	}

	return count;
}



int main(){
	string a, b;
	cin >> a >> b;
	cout << kSimilarity(a, b) << "\n";
	return 0;
}



