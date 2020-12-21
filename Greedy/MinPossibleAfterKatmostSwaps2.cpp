#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>

using namespace std;

class Solution{
public:
	string minInteger(string num, int k){
		int n = num.size();
		if(k >= n*n){
			sort(num.begin(), num.end());
			return num;
		}

		for(int i=0;i<n;i++){
			int j = i + 1, ct = 0, minvalue = num[i], minIdx = -1;
			while(j < n && ct+1 <= k){
				if(minvalue > num[j]) minvalue = num[j], minIdx = j;
				j++, ct++;
			}
			if(minIdx == -1) continue;
			for(int k = minIdx;k > i;k--) num[k] = num[k - 1];
			num[i] = char(minvalue);
			k -= minIdx - i;
		}
		return num;
	}
};

//	More Efficient Alg
string minInteger(string num, int k){
	int n = num.size();
	if(k >= n*n){
		sort(num.begin(), num.end());
		return num;
	}

	vector< priority_queue<int, vector<int>, greater<int> ()> > q(10);
	for(int i=0;i<n;i++) q[num[i] - '0'].push_back(i);

	string res = "";
	for(int i=0;i<n;i++){

		int curr = num[i] - '0';
		for(int j=0;j<curr;j++){
			while(!q[j].empty() && q[j].top() < i) q[j].pop();
			if(q[j].empty()) continue;

			
		}
	}
	return res;
}











