#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <set>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>
#define vvb vector<vb>


void dfs(int idx, vvi &adj, unordered_map<int,int> &solution, int &counter){

	solution[idx] = counter;

	for(int &next: adj[idx]){
		if(solution.count(next) == 0) dfs(next, adj, solution, counter);
	}

}

bool equationsPossible(vector<string> &equations){

	unordered_map<string, int> mp;
	int counter = 0;

	for(string &s: equations){
		string a = s.substr(0, 1), b = s.substr(3, 1);
		if(mp.count(a) == 0) mp[a] = counter++;
		if(mp.count(b) == 0) mp[b] = counter++;
	}

	int size = mp.size();
	vvi adj(size, vi());

	for(string &s: equations){

		if(s.substr(1,2) == "=="){
			int st = mp[s.substr(0, 1)], en = mp[s.substr(3, 1)];
			adj[st].push_back(en), adj[en].push_back(st);
		}
	}

	unordered_map<int,int> solution;
	counter = -1;
	for(int i = 0;i < size;i++){
		if(solution.count(i) == 0){
			dfs(i, adj, solution, ++counter);
		}
	}

	for(string &s: equations){
		if(s.substr(1, 2) == "!="){
			int st = mp[s.substr(0, 1)], en = mp[s.substr(3, 1)];
			if(solution.count(st) == 0 || solution.count(en) == 0) continue;
			if(solution[st] == solution[en]) return false;
		}
	}
	return true;
}

//	Union find Alg
class Node{
public:
	int parent, rank;
	Node(int p = 0): parent(p), rank(0) {}
};

class DsjSet{
public:
	int size;
	vector<Node> dsuf;
	DsjSet(int size = 26): size(size){
		for(int i=0;i<size;i++) dsuf.push_back(i);
	}
	
	int find(int v){
		if(dsuf[v].parent == v) return v;
		else return dsuf[v].parent = find(dsuf[v].parent);//	Path Compression
	}

	void union_op(int fromP,int toP){
		//Assuming fromP and toP are absolute parents

		if(dsuf[fromP].rank < dsuf[toP].rank) dsuf[fromP].parent = toP;
		else if(dsuf[fromP].rank > dsuf[toP].rank) dsuf[toP].parent = fromP;
		else{
			dsuf[fromP].parent = toP;
			dsuf[toP].rank += 1;
		}
	}
};

bool equationsPossible2(vector<string> &equations){

	DsjSet dj;
	for(string &s: equations){
		int i = s[0] - 'a', j = s[3] - 'a';
		if(s.substr(1,2) == "=="){
			int fromP = dj.find(i), toP = dj.find(j);
			if(fromP != toP) dj.union_op(fromP, toP);
		}
	}

	for(string &s: equations){
		int i = s[0] - 'a', j = s[3] - 'a';
		if(s.substr(1,2) == "!="){
			int fromP = dj.find(i), toP = dj.find(j);
			if(fromP == toP) return false;
		}
	}
	return true;
}


int main(){
	return 0;
}

