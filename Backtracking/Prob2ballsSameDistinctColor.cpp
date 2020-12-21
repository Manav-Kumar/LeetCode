#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <random>
using namespace std;

#define vi vector<int>

class Solution{
	long long valid_ways, total_ways, total;
	int C[7][7];
public:
	void backtracking(int idx, int currCount, int k1, int k2,double p, vi &balls){

		if(idx == balls.size()){
			if(currCount == total){
				valid_ways += (k1 == k2)*p;
				total_ways += p;
			}
			return;
		}

		for(int ct = 0;ct <= balls[idx];ct++){
			if(ct + currCount > total) return;
			backtracking(idx + 1, currCount + ct, k1 + (ct>0) , k2 + (balls[idx] - ct > 0),
			p* C[balls[idx]][ct], balls);
		}
	}

	double getProability(vector<int> &balls){
		total_ways = 0, valid_ways = 0, total = 0;
		for(int &a: balls) total += a;
		total /= 2;

		C[1][0] = 1, C[1][1] = 1;
		for(int i=2;i<=6;i++){
			for(int k=0;k<=i/2;k++){
				if(k == 0) C[i][k] = 1;
				else C[i][k] = i*C[i - 1][k - 1]/k;

				C[i][i - k] = C[i][k];
			}
		}
		backtracking(0, 0, 0, 0, 1, balls);
		cout << valid_ways << " " << total_ways << "\n";
		return (double)valid_ways/total_ways;
	}
};


int main(){
	int k;
	cin >> k;
	vi balls(k);
	for(int &a: balls) cin >> a;
	Solution s;
	cout << s.getProability(balls) << "\n"; 
	return 0;
}




