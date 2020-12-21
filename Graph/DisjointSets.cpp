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

//	2 or more sets with nothing in common is called DisJoint Sets 
//	Performs majorily 2 operations, Find, Union(taking union of 2 sets is similar to taking
//		unions of 2 elements)

//	We will be doing Union By rank and in between Path Compression as well

//	It is only applicable for Undirected Graphs, doesn't care about edges direction

class Node{
public:
	int parent, rank;
	Node(int p = 0): parent(p), rank(0) {}
};

class DisSet{
public:
	int size;
	vector<Node> arr;
	DisSet(int size): size(size){
		for(int i = 0;i< size;i++) arr.push_back(Node(i));
	}
	int find(int i){
		if(arr[i].parent == i) return i;
		int p = find(arr[i].parent);
		arr[i].parent = p;
		return p;
		//else return arr[i].parent = find(arr[i].parent);//	Path Compression

	}
	void union_op(int fromP,int toP){
		//	fromP and toP are absolute parents belonging to different sets

		if(arr[fromP].rank > arr[toP].rank){
			arr[toP].parent = fromP;
		}
		else if(arr[fromP].rank < arr[toP].rank){
			arr[fromP].parent = toP;
		}
		else{
			arr[fromP].parent = top;
			arr[toP].rank += 1;//	Increase rank of parent
		}

	}
}

class DisSet{
public:
	vi parent;
	int size;
	DisSet(int size): size(size){
		parent = vi(size);
		for(int i=0;i<size;i++) parent[i] = i;
	}
	
	int find(int i){
		if(parent[i] == i) return i;
		int p = parent[i];
		parent[i] = p;
		return p;
	}

	void merge(int i,int j){
		int p = find(i), q = find(j);
		parent[p] = q;
	}
};

int main(){
	return 0;
}


