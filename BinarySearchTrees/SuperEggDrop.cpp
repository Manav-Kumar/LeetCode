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
#include <deque>
using namespace std;

int superEggDrop(int K,int N){

	// double temp = log(double(N));
	// if(double(K) >= temp){
	// 	if(K == temp) return temp;
	// 	return (int)temp + 1;
	// }

	int st = 0, en = N,k = K;
	while(k > 1 && st < en){
		int mid = (st + en + 1)/2;
		k--;
		if(mid == 0) return K - k;
		en = mid - 1;
	}
	return K - 1 + (en - st);
}

int main(){
	int N,K;
	cin >> K >> N;
	cout << superEggDrop(K,N) << "\n";
	return 0;
}