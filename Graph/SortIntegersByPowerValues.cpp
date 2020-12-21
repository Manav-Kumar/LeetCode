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

int getAns(int i,unordered_map<int,int> &solution){

	if(solution.count(i) == 0){
		if(i%2 == 0) solution[i] = getAns(i/2, solution);
		else solution[i] = getAns(3*i + 1, solution);
	}
	return solution[i] + 1;
}

class comparator{
public:
	bool operator()(const pair<int,int>& p, const pair<int,int> &q){
		if(p.first == q.first) return p.second < q.second;
		return p.first < q.first;
	}
};

int getKth(int lo,int hi,int k){
	unordered_map<int,int> solution;
	priority_queue<pair<int,int>, vector<pair<int,int> >, comparator> pq;
	solution[1] = 0;
	for(int i = lo;i <= hi;i++){
		if(i%2 == 0) solution[i] = getAns(i/2, solution);
		else solution[i] = getAns(3*i + 1, solution);

		pq.push({solution[i], i});
		if(pq.size() > k) pq.pop();
	}

	return pq.top().second;
}

int main(){
	int lo, hi, k;
	cin >> lo >> hi >> k;
	cout << getKth(lo, hi, k) << "\n";
	return 0;
}

