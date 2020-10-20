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
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vl vector<long>
#define vll vector<long long>
#define vc vector<char>
#define vs vector<string>
#define vvc vector<vc>
#define vvi vector<vector<int> >
#define vvl vector<vl>
#define vvll vector<vll>
#define vvb vector<vector<bool> >


bool checkMaxHeap(int arr[],int n,int idx = 0)
{
	if(idx >= n) return true;
	int lci = 2*idx + 1;
	int rci = 2*idx + 2;
	if(lci >= n) return true;

	if(arr[idx] < arr[lci]) return false;
	if(rci < n && arr[idx] < arr[rci]) return false;

	return checkMaxHeap(arr, n, lci) && checkMaxHeap(arr, n, rci);
}

//	Kth Largest Element
int KthLargest(vector<int> arr,int n,int k)
{
	priority_queue<int, vector<int>, greater<int> > pq;
	for(int i=0;i<k&&i<n;i++) pq.push(arr[i]);
	for(int i=k;i<n;i++)
	{
		if(arr[i] > pq.top())
		{
			pq.pop();
			pq.push(arr[i]);
		}
	}
	return pq.top();
}

//Merge K Sorted Arrays
class comparator
{
public:
	bool operator()(const pair<int,int>& a,const pair<int,int>& b){
		return a.first > b.first;
	}
};

vector<int> mergeKSortedArrays(vector<vector<int>* > input)
{
	vector<int> result;
	priority_queue<pair<int,int> , vector<pair<int,int> >, comparator > pq;
	int k = input.size();
	for(int i=0;i<k;i++) pq.push(pair<int,int>(input[i]->at(0), i));
	vector<int> currIdx(k, 0);
	while(!pq.empty())
	{
		pair<int,int> top = pq.top();
		pq.pop();
		result.push_back(top.first);
		currIdx[top.second]++;
		int arrIdx = top.second, eleIdx = currIdx[top.second];
		if(eleIdx < input[arrIdx]->size()) pq.push(pair<int,int>(input[arrIdx]->at(eleIdx), arrIdx));
	}
	return result;
}


//	Running median
void findMedian(int arr[],int n)
{
	priority_queue<int> leftMax;
	priority_queue<int, vector<int>, greater<int> > rightMin;
	cout << arr[0] << "\n";
	rightMin.push(arr[0]);
	for(int i=1;i<n;i++)
	{
		if(arr[i] < rightMin.top()) leftMax.push(arr[i]);
		else rightMin.push(arr[i]);

		if(int(leftMax.size() - rightMin.size()) > 1){
			rightMin.push(leftMax.top());
			leftMax.pop();
		}

		if(int(rightMin.size() - leftMax.size()) > 1){
			leftMax.push(rightMin.top());
			rightMin.pop();
		}

		if(leftMax.size() == rightMin.size()){
			cout << (leftMax.top() + rightMin.top())/2 << "\n";
		}
		else{
			int ans = leftMax.size() > rightMin.size()?leftMax.top(): rightMin.top();
			cout << ans << "\n";
		}
	}

	return ;
}

int main()
{
	// int k,c,d;
	// cin >> k;
	// vector<vector<int>* > input = vector<vector<int>* >();
	// for(int i=0;i<k;i++)
	// {
	// 	cin >> c;
	// 	vector<int> *a = new vector<int>();
	// 	for(int j=0;j<c;j++)
	// 	{
	// 		cin >> d;
	// 		a->push_back(d);
	// 	}
	// 	input.push_back(a);
	// }
	// vector<int> result = mergeKSortedArrays(input);
	// for(int a: result) cout << a << " ";
	int arr[5] = {5, 4, 3, 2, 1};
	findMedian(arr,5);
	return 0;
}


