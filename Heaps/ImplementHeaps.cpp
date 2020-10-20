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



class MaxHeap
{
public:
	int nextIdx,size;
	int *arr;
	MaxHeap()
	{
		nextIdx = 0;
		arr = new int[2];
		size = 2;
	}
	int getMax()
	{
		if(nextIdx == 0)
		{
			cout << "No element is there to return " << "\n";
			return INT_MIN; 
		}
		return arr[nextIdx-1];
	}
	void UpHeapify(int idx)
	{
		while(idx != 0)
		{
			int parent = (idx - 1)/2;
			if(arr[parent] < arr[idx]) swap(arr[parent], arr[idx]);
			else break;
			idx = parent;
		}
	}
	void insert(int value)
	{
		if(nextIdx == size)
		{
			int *temp = new int[2*size];
			for(int i=0;i<size;i++) temp[i] = arr[i];
			delete []arr;
			arr = temp;
			size *= 2;
		}
		arr[nextIdx] = value;
		nextIdx++;
		UpHeapify(nextIdx - 1);
	}

	void DownHeapify(int idx)
	{
		while(idx < nextIdx)
		{
			int leftChild = (2*idx+1), rightChild = (2*idx+2), index = idx;
			if(leftChild < nextIdx && arr[index] < arr[leftChild]) index = leftChild;
			if(rightChild < nextIdx && arr[index] < arr[rightChild]) index = rightChild;

			if(index == idx) break;
			swap(arr[index], arr[idx]);
			idx = index;
		}
	}
	int removeMax()
	{
		if(nextIdx == 0)
		{
			cout << "No element is there to return " << "\n";
			return INT_MIN; 
		}
		int ans = arr[0];
		swap(arr[0], arr[nextIdx - 1]);
		DownHeapify(0);
		return ans;
	}
};


class MinHeap
{
public:
	int nextIdx, size;
	int *arr;
	MinHeap()
	{
		nextIdx = 0;
		arr = new int[2];
		size = 2;
	}
	int getMin()
	{
		if(nextIdx == 0) return INT_MAX;
		return arr[nextIdx-1];
	}
	void UpHeapify(int idx)
	{
		int parent;
		while(idx != 0)
		{
			parent = (idx - 1)/2;
			if(arr[idx] < arr[parent]) swap(arr[parent], arr[idx]);
			else break;
			idx = parent;
		}
	}
	void insert(int value)
	{
		if(nextIdx == size)
		{
			int *temp = new int[2*size];
			for(int i=0;i<size;i++) temp[i] = arr[i];
			delete []arr;
			arr = temp;
			size *= 2;
		}
		arr[nextIdx] = value;
		nextIdx++;
		UpHeapify(nextIdx - 1);
	}
	void DownHeapify(int idx)
	{
		while(1 )
		{
			int leftChild = (2*idx + 1), rightChild = (2*idx + 2), index = idx;
			if(leftChild < nextIdx && arr[index] > arr[leftChild]) index = leftChild;
			if(rightChild < nextIdx && arr[index] > arr[rightChild]) index = rightChild;
			if(index == idx) break;
			swap(arr[index], arr[idx]);
			idx = index;
		}
	}
	int removeMin()
	{
		if(nextIdx == 0)
		{
			cout << "No element to delete " << "\n";
			return INT_MAX;
		}
		int ans = arr[0];
		swap(arr[0], arr[nextIdx - 1]);
		nextIdx--;
		DownHeapify(0);
		return ans;
	}
};


class PriorityQueue
{
	vector<int> pq;
public:
	bool isEmpty(){
		return pq.size() == 0;
	}
	int getSize(){
		return pq.size();
	}
	int getMin(){
		if(isEmpty()){
			return 0;	//Priority Queue is Empty
		}
		return pq[0];
	}

	void insert(int value){
		pq.push_back(value);
		int childIndex = pq.size() - 1;
		while(childIndex > 0)
		{
			int parentIndex = (childIndex - 1)/2;
			if(pq[childIndex] < pq[parentIndex]){
				int temp = pq[childIndex];
				pq[childIndex] = pq[parentIndex];
				pq[parentIndex] = temp;
			}
			else break;
			childIndex = parentIndex;
		}
	}

	int removeMin()
	{
		if(isEmpty()){
			return 0;//Priority Queue is Empty
		}
		int ans = pq[0];
		pq[0] = pq[pq.size() - 1];
		pq.pop_back();
		int parentIndex = 0;
		while(parentIndex < pq.size())
		{
			int lci = 2*parentIndex + 1, rci = 2*parentIndex + 2, minIndex = parentIndex;
			if(lci < pq.size() && pq[minIndex] > pq[lci]) minIndex = lci;
			if(rci < pq.size() && pq[minIndex] > pq[rci]) minIndex = rci;
			if(minIndex == parentIndex) break;
			swap(pq[minIndex], pq[parentIndex]);
			parentIndex = minIndex; 
		}
		return ans;
	}
};


//	Space Complexity -> O(1)
void up_heapify(vector<int> &a,int childIndex)
{
	while(childIndex > 0)
	{
		int parentIndex = (childIndex - 1)/2;
		if(a[childIndex] < a[parentIndex]) swap(a[parentIndex], a[childIndex]);
		else break;
		childIndex = parentIndex;
	}
}


void down_heapify(vector<int> &a,int size,int parentIndex)
{
	int leftChild = 2*parentIndex + 1;
	int rightChild = 2*parentIndex + 2;
	while(leftChild < size)
	{
		int minIndex = parentIndex;
		if(a[minIndex] > a[leftChild]) minIndex = leftChild;
		if(rightChild < size && a[minIndex] > a[rightChild]) minIndex = rightChild;
		if(minIndex == parentIndex) break;
		swap(a[parentIndex], a[minIndex]);
		parentIndex = minIndex;
		leftChild = 2*parentIndex + 1;
		rightChild = 2*parentIndex + 2;
	}
}

void InplaceheapSort(vector<int> &a)
{
	int n = a.size();
	for(int i=1;i<n;i++) up_heapify(a,i);

	int lastIndex = n;
	while(lastIndex > 1)
	{
		swap(a[0], a[lastIndex - 1]);
		lastIndex--;
		down_heapify(a,lastIndex, 0);
	}
}


int main()
{
	//In built Priority Queue
	priority_queue<int> pq;
	return 0;
}

