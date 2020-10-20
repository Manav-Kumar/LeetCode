#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <cmath>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define ll long long


//	Binary Lifting

class TreeAncestor{
	vector<int> arr;
	int lca[50001][20];
	int n;
public:
	TreeAncestor(int n, vector<int> &parent): n(n) {
		for(int &a: parent) arr.push_back(a);
		int LN = ceil(log2(n));

		for(int j = 0;j <= LN;j++){
			for(int i = 0;i < n;i++) lca[i][j] = -1;
		}

		for(int i = 0;i < n;i++) lca[i][0] = arr[i];

		for(int j = 1;j <= LN;j++){
			for(int i = 0;i < n;i++){
				int par = lca[i][j-1];
				if(par == -1) lca[i][j] = -1;
				else lca[i][j] = lca[lca[i][j-1]][j-1];
			}
		}
	}
	
	int getKthAncestor(int node,int k){

		for(int i = 0;int(1<<i) <= k && node != -1;i++){
			if(k & int(1<<i)){
				node = lca[node][i];
			}
		}

		return node;
	}
};


int main(){
	int n;
	cin >> n;
	return 0;
}



