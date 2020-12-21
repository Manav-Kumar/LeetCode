#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>

long MOD = 1e9 + 7;

void backtracking(vector<int> &A,long &sum, int idx = 0,int small = 20001, int big = 0){

	if(idx == A.size()){
		if(big != 0) sum = (sum + big - small)%(MOD);
		return ;
	}


	backtracking(A, sum, idx + 1, small, big);
	backtracking(A, sum, idx + 1, min(small, A[idx]), max(big, A[idx]));
}

int sumSubseqWidths(vector<int> &A){
	vi temp;
	long sum = 0;
	backtracking(A, sum);
	return sum;
}

long power[20001];

void Fillpowers(){
	power[0] = 1;
	for(int i=1;i<=20000;i++){
		power[i] = (power[i - 1]*2)%MOD;
	}
}

int sumSubseqWidths2(vi &A){
	sort(A.begin(), A.end());
	Fillpowers();
	int n = A.size();
	long sum = 0;
	for(int i = 0;i<A.size();i++){

		// for(int j = i+1;j<A.size();j++){
		// 	sum += (power[j - i - 1]*A[j])%MOD;
		// 	sum -= (power[j - i - 1]*A[i])%MOD;
		// 	sum = (sum + MOD)%MOD;
		// }
		//	OR

		sum += (power[i]*A[i])%MOD;
		sum -= (power[n - i - 1]*A[i])%MOD;
		sum = (sum + MOD)%MOD;

	}
	return sum;
}

int main(){
	int n;
	cin >> n;
	vi A(n);
	for(int &a: A) cin >> a;
	cout << sumSubseqWidths2(A) << "\n";
	return 0;
}

