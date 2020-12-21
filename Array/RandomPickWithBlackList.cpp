#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>
#define rep(i, a, b) for(int i = a;i<b;i++)

// class Solution{
// public:
// 	int N, realsize;
// 	vector<int> blacklist;
// 	Solution(int n, vector<int> &blist){
// 		N = n, blacklist = blist, realsize = n  - blist.size();
// 		sort(blacklist.begin(), blacklist.end());
// 	}

// 	int pick(){
// 		return 0;
// 	}
// };

//	Random Pick With Weight
class Solution{
public:
	vector<int> cumSum;
	long long sum;
	Solution(vector<int> &w): cumSum(w.size(), 0), sum(0) {
		for(int i=0;i<w.size();i++){
			sum += w[i];
			if(i == 0) cumSum[i] = w[i];
			else cumSum[i] = cumSum[i - 1] + w[i];
		}
	}

	int BinarySearch(vector<int> &cumSum, int val){
		int st = 0, en = cumSum.size() - 1, ans = -1;
		while(st <= en){
			int mid = (st + en)/2;
			if(cumSum[mid] == val) return mid;
			else if(cumSum[mid] > val) ans = mid, en = mid - 1;
			else if(cumSum[mid] < val) st = mid + 1;
		}
		return ans;
	}

	int pickIndex(){
		return upper_bound(cumSum.begin(), cumSum.end(), rand()%sum) - cumSum.begin();
	}
};

int main(){
	rep(i, 0, 5) cout << rand() << " ";
	return 0;
}









