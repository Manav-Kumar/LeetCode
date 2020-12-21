#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
using namespace std;

class Node{
public:
	int val;
	vector<Node*> neighbors;
	Node(int _val): val(_val) {}

	Node(int _val, vector<Node*> const &_neighbors){
		val = _val;
		neighbors = _neighbors;
	}
};

//	DFS
Node* cloneGraph(Node* node, unordered_map<int, Node*> &visited){

	if(visited.count(node->val) > 0) return visited[node->val];

	Node* copy = new Node(node->val);
	visited[node->val] = copy;

	for(Node* next: node->neighbors){
		copy->neighbors.push_back(cloneGraph(next, visited));
	}
	return copy;
}

//	BFS
Node* cloneGraph(Node* node){
	Node* root = new Node(node->val);
	unordered_map<int, Node*> visited;
	queue<pair<Node*,Node*> > pq;
	pq.push({root, node});
	visited[root->val] = root;
	while(!pq.empty()){
		Node* copy = pq.front().first;
		Node* node = pq.front().second; pq.pop();

		for(Node* next: node->neighbors){
			if(visited.count(next->val) == 0){
				visited[next->val] = new Node(next->val);
				pq.push({visited[next->val], next]});
			}
			copy->neighbors.push_back(visited[next->val]);
		}
	}
	return root;
}


int main(){
	unordered_map<int, Node*> visited;
	bool checkRoot = true;
	Node*root = NULL;

	return 0;
}



