#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>

bool isSimilar(string &a, string &b){
	//	Both strings begin anagrams
	int diff = 0;
	for(int i=0;i<a.size();i++){
		if(a[i] != b[i]) diff++;
		if(diff > 2) return false;
	}
	return true;
}

void dfs(unordered_map<string, vector<string> > &edges, unordered_set<string> &visited,
		string start){
	visited.insert(start);
	for(string &next: edges[start]){
		if(visited.count(next) == 0) dfs(edges, visited, next);
	}
}


int numSimilarGroups(vector<string> &A){
	unordered_map<string, vector<string> > edges;
	for(int i=0;i<A.size();i++){
		for(int j=i+1;j<A.size();j++){
			if(isSimilar(A[i], A[j])) edges[A[i]].push_back(A[j]), edges[A[j]].push_back(A[i]);
		}
	}

	int ans = 0;
	unordered_set<string> visited;
	for(string &a: A){
		if(visited.count(a) == 0){
			ans++;
			dfs(edges, visited, a);
		}
	}

	return ans;
}


class DSU{
public:
	vector<pair<int,int> > parent;
	int numberComp = 0;

	DSU(int n): parent(n), numberComp(n){
		for(int i=0;i<n;i++) parent[i] = pair<int,int> (i, 1);
	}

	int find(int a){
		if(parent[a].first == a) return a;
		else return parent[a].first = find(parent[a].first);
	}

	void merge(int a,int b){
		//	Assuming a and b are absolute parent
		numberComp--;
		if(parent[a].second == parent[b].second){
			parent[a].first = b, parent[b].second += 1;
		}
		else if(parent[a].second > parent[b].second) parent[b].first = a;
		else if(parent[a].second < parent[b].second) parent[a].first = b;

	}

	int UniqueElement(){
		return numberComp;
	}
};

int numSimilarGroups2(vector<string> &A){
	unordered_map<string, int> hash;
	int count = 0;
	vector<string> arr;
	for(string &a: A){
		if(hash.count(a) == 0) arr.push_back(a), hash[a] = count++;
	}

	DSU Dsjt(arr.size());

	for(int i=0;i<arr.size() - 1;i++){//	1st word
		for(int j = i + 1;j < arr.size();j++){

			if(isSimilar(arr[i], arr[j])){
				int pa = Dsjt.find(i), pb = Dsjt.find(j);
				if(pa != pb) Dsjt.merge(pa, pb);
			}
		}
	}

	return Dsjt.UniqueElement();

}

int main(){
	int n;
	cin >> n;
	vector<string> A(n);
	for(string &s: A) cin >> s;
	cout << numSimilarGroups2(A) << "\n";
	return 0;
}



