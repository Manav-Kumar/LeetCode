#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <random>
using namespace std;

#define vi vector<int>

class ProductOfNumbers{
public:
	vector<vector<int> > v;
	ProductOfNumbers(){

	}

	void add(int num){
		if(v.empty()){
			v.push_back(vi(101, 0));
			v[0][num] += 1;
			return;
		}
		int ld = v.size() - 1;
		vi last = v[ld];
		last[num] += 1;
		v.push_back(last);
	}

	int getProduct(int k){
		int ld = v.size() - 1, ret = 1;

		vi ans = v[ld];
		if(ld - k >= 0){
			for(int ct = 0;ct <= 100;ct++){
				ans[ct] -= v[ld - k][ct];
			}
		}

		for(int ct = 0;ct <= 100;ct++){
			if(ans[ct] > 0) ret *= pow(ct, ans[ct]);
		}
		return ret;
	}
};


class ProductOfNumbers{
public:
	vector<int> v;
	ProductOfNumbers(){

	}

	void add(int num){
		if(num == 0) v.clear();
		else if(v.empty()) v.push_back(num);
		else v.push_back(v[v.size() - 1]*num);
		
	}

	int getProduct(int k){
		if(k > v.size()) return 0;
		else if(k == v.size()) return v[v.size() - 1];
		else return v[v.size() - 1]/v[v.size() - 1 - k];

	}
};


int main(){

	return 0;
}

