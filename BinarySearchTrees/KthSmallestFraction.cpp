#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <list>
#include <queue>
using namespace std;

#define vb vector<bool>
#define vi vector<int>
#define vvb vector<vb>
#define vvi vector<vi>

class fractions{
public:
	double p,q, ft;
	fractions(double p = 1,double q = 1): p(p), q(q), ft(p/q) {}
};

bool compare(fractions &a, fractions &b){
	return a.ft <= b.ft;
}

// vector<int> kthSmallestPrimeFraction(vector<int> &A,int k)
// {
// 	int n = A.size();
// 	vector<fractions> arr;
// 	for(int i=0;i<n;i++){
// 		for(int j = i+1;j < n;j++){
// 			arr.push_back(fractions(A[i], A[j]));
// 		}
// 	}

// 	sort(arr.begin(), arr.end(), compare);
// 	return vector<int> {int(arr[k-1].p), int(arr[k-1].q)};
// }

class node{
public:
	int p,q;
	double value;
	node(int p = 2,int q = 2,double v = 12): p(p), q(q), value(v) {}
};

class comparator{
public:
	bool operator() (node a, node b){
		return a.value > b.value;
	}
};


vector<int> kthSmallestPrimeFraction(vector<int> &A,int k){
	priority_queue<node, vector<node>, comparator > pq;

	for(int i=0;i<A.size()-1;i++){
		pq.push(node(i, A.size()-1, 1.0*A[i]/A.back()) );
	}

	while(--k > 0){
		node curr = pq.top();
		pq.pop();
		curr.q--;
		pq.push(node(curr.p, curr.q, 1.0*A[curr.p]/A[curr.q] ));
	}
	return vector<int> {A[pq.top().p], A[pq.top().q]};
}

int main(){
	int n, k;
	cin >> n;
	vector<int> A(n);
	for(int &a: A) cin >> a;
	cin >> k;
	vector<int> ans = kthSmallestPrimeFraction(A, k);
	cout << ans[0] << " " << ans[1] << "\n";
	return 0;
}

