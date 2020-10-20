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


class Solution{

	class DSU{
		int* root;
	public:
		int count;
		DSU(int n){
			root = new int[(n + 1)*(n + 1)];
			count = 1;

			for(int i = 0;i <= n;i++){
				for(int j = 0;j <= n;j++){
					int idx = i * (n + 1) + j;
					if(i == 0 || i == n || j == 0 || j == n){
						root[idx] = 0;
					}
					else root[idx] = idx;
				}
			}
		}

		int find(int x){
			if(root[x] != x) root[x] = find(root[x]);
			return root[x];
		}
		void TakeUnion(int x,int y){
			int rootX = find(x), rootY = find(y);
			if(rootX == rootY){
				count++;
				return;
			}
			root[rootY] = rootX;
		}
	};

public:
	int regionsBySlashes(vs &grid){
		int n = grid.size();
		DSU d(n);
		for(int i = 0;i< n;i++){
			for(int j = 0;j < n;j++){
				char c = grid[i][j];

				if(c == '/'){
					int x = i * (n + 1) + j + 1, y = (i + 1) * (n + 1) + j;
					d.TakeUnion(x, y);
				}
				else if(c == '\\'){
					int x = i * (n + 1) + j, y = (i + 1) * (n + 1) + j + 1;
					d.TakeUnion(x, y);
				}
			}
		}
		return d.count;
	}
};


//	Another 

void merge(vi &dsu, int a,int b){

	while(dsu[a] != a) a = dsu[a];
	while(dsu[b] != b) b = dsu[b];

	if(a != b) dsu[b] = a; 
}

int regionsBySlashes2(vs &grid){
	int n = grid.size();
	vi dsu(n*n*4);
	for(int i = 0;i < dsu.size();i++) dsu[i] = i;

	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			char c = grid[i][j];

			int base = (i*n + j)*4;
			if(c == ' '){
				merge(dsu, base + 0, base + 1);
				merge(dsu, base + 1, base + 2);
				merge(dsu, base + 2, base + 3);
			}
			else if(c == '/'){
				merge(dsu, base + 0, base + 3);
				merge(dsu, base + 1, base + 2);
			}
			else if(c == '\\'){
				merge(dsu, base + 0, base + 1);
				merge(dsu, base + 2, base + 3);
			}

			if(j < n - 1){
				merge(dsu, base + 1, base + 7);
			}
			if(i < n-1){
				merge(dsu, base + 2, ((i + 1)*n + j)*4 );
			}
		}
	}
	int ans = 0;
	for(int i = 0;i < dsu.size();i++) if(dsu[i] == i) ans++;

	return ans;
}

int main(){
	int n;
	cin >> n;
	vs grid(n);
	for(string &s: grid) cin >> s;
	cout << grid[0].size() << "\n";
	return 0;
}







