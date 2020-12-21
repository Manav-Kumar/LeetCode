#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

#define mod 1e9 + 7;

typedef long long ll;

int xdir[] = {-1, 0, 1, 0};
int ydir[] = {0, 1, 0, -1};
class Solution{
	int ***visited;
	bool OutOfBoundary(int m,int n,int i,int j){
		return i < 0 || j < 0 || i >= m || j >= n;
	}
public:
	//	Initialize the visited array
	int findPaths(int m,int n, int N, int i,int j){
		if(OutOfBoundary(m, n, i, j)) return 1;
		if(N <= 0) return 0;
		if(visited[N][i][j] != -1) return visited[N][i][j];
		ll ans = 0;
		for(int k=0;k<4;k++){
			ans += findPaths(m, n, N - 1, i + xdir[k], j + ydir[k]);
			ans %= mod;
		}
		return visited[N][i][j] = ans;
	}
};

//	Knight Probability in Chess Board
int dmoves[] = {-2, 2};
int smoves[] = {-1, 1};
class Solution{
	int cMoves, incMoves;
public:
	void knightProbability(int N,int K,int int r,int c){
		if(r < 0 || c < 0 || r >= N || c >= N){
			incMoves += 1;
			return;
		}
		if(K == 0){
			cMoves += 1;
			return;
		}
		cMoves = 0, incMoves = 0;
		//	X 2 moves
		for(int k=0;k<2;k++){
			for(int z=0;z<2;z++){
				knightProbability(N, K - 1, r + dmoves[k], c + smoves[z]);
				knightProbability(N, K - 1, r + smoves[z], c + dmoves[k]);
			}
		}
	}
	
};

int main(){

	return 0;
}




