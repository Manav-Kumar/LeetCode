#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
#include <set>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>
#define vvb vector<vb>

bool dfs(vvi &graph, vb &visited, int idx,set<int> &a, set<int> &b){

	a.insert(idx), visited[idx] = true;
	for(int &next: graph[idx]){
		if(!visited[next]){
			if(!dfs(graph, visited, next, b, a)) return false;
		}
		else if(a.count(next) > 0) return false;
	}
	return true;
}

bool isBipartite(vvi &graph){
	int n = graph.size();
	set<int> a, b;
	vb visited(n, false);
	for(int i=0;i<n;i++){
		if(!visited[i]){
			if(!dfs(graph, visited, i, a, b)) return false;
		}
	}
	return true;
}

//	Possible Bipartition

class Node{
public:
	int parent, rank;
	Node(int p = -1): parent(p), rank(0) {}
};

class DsjSet{
public:
	vector<Node> arr;
	DsjSet(int size){
		for(int i=0;i<size;i++) arr.push_back(Node(i));
	}
	
	int find(int v){
		if(arr[v].parent == v) return v;
		else return arr[v].parent = find(arr[v].parent);
	}

	void union_op(int fromP,int toP){

		if(arr[fromP].rank < arr[toP].rank) arr[fromP].parent = toP;
		else if(arr[fromP].rank > arr[toP].rank) arr[toP].parent = fromP;
		else{
			arr[fromP].parent = toP;
			arr[toP].rank += 1;
		}
	}
};

bool dfs(vvi &adj, vi &visited,int idx,int color){
	visited[idx] = color;
	for(int &next: adj[idx]){
		if(visited[next] == 0){
			if(!dfs(adj, visited, next, color == 1?2:1)) return false;
		}
		else if(visited[next] == color) return false;
	}

	return true;
}

bool possibleBipartition(int N, vvi &dislikes){
	vvi adj(N, vi());
	for(vi &edge: dislikes){
		adj[edge[0] - 1].push_back(edge[1] - 1);
		adj[edge[1] - 1].push_back(edge[0] - 1);
	}

	vi visited(N, 0);
	set<int> a, b;
	for(int i=0;i<N;i++){
		if(!visited[i]) if(!dfs(adj, visited, i, 1)) return false;
	}
	return true;
}

//	Minimum Number of Vertices to Reach All Nodes

void AcyclicDFS(vvi &adj, vb &visited, int idx,stack<int>& s){

	visited[idx] = true;
	for(int &next: adj[idx]){
		if(!visited[idx]) AcyclicDFS(adj, visited, next, s);
	}
	s.push(idx);
}

void AcyclicDFS(vvi &adj, vb &visited, int idx){
	visited[idx] = true;
	for(int &next: adj[idx]){
		if(!visited[idx]) AcyclicDFS(adj, visited, next);
	}
}

vector<int> findSmallestSetOfVertices(int n, vvi &edges){
	vvi adj(n, vi());
	for(vi &a: edges){
		adj[a[0]].push_back(a[1]);
	}
	vb visited(n, false);
	stack<int> s;
	for(int i=0;i<n;i++){
		if(!visited[i]){
			AcyclicDFS(adj, visited, i, s);
		}
	}
	visited.clear(), visited.resize(n, false);
	vi ans;
	while(!s.empty()){
		if(!visited[s.top()]){
			ans.push_back(s.top());
			AcyclicDFS(adj, visited, s.top());
		}
		s.pop();
	}
	return ans;
}

//	Indegree Solution
vi findSmallestSetOfVertices2(int n, vvi &edges){
	//	Vertices With 0 indegree is our solution
	vi indegree(n, 0), ans;
	for(vi &a: edges){
		indegree[a[1]] += 1;
	}
	for(int i=0;i<n;i++){
		if(indegree[i] == 0) ans.push_back(i);
	}
	return ans;
}

int main(){
	int n, b, c;
	cin >> n;
	vvi graph(n, vi());
	for(vi &a: graph){
		cin >> b;
		for(int i=0;i<b;i++){
			cin >> c;
			a.push_back(c);
		}
	}
	cout << isBipartite(graph) << "\n"; 
	return 0;
}

