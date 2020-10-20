#include <iostream>
using namespace std;

int query(int *BIT,int idx){

	int sum = 0;
	for(;idx > 0;idx -= (idx&(-idx))){
		sum += BIT[idx];
	}
	return sum;
}

void update(int idx,int *BIT,int n,int value = 1){

	for(;idx <= n;idx += (idx&(-idx))){
		BIT[idx] += 1;
	}
}

class Coder{
public:
	int x, y, No;
};

bool compare(Coder &a, Coder &b){
	if(a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

int main(){
	int n, maxBitvalue = 0;
	cin >> n;
	Coder* arr = new Coder[n];
	for(int i=0;i<n;i++){
		cin >> arr[i].x >> arr[i].y;
		arr[i].No = i;
		maxBitvalue = max(maxBitvalue, arr[i].y);
	}
	sort(arr, arr + n, compare);
	int *BIT = new int[maxBitvalue+1]();
	int *ans = new int[n]();
	for(int i = 0;i < n;){

		int endIdx = i;
		while(endIdx < n && arr[i].x == arr[endIdx].x && arr[i].y == arr[endIdx].y) endIdx++;

		//	Query
		for(int j=i;j<endIdx;j++){
			ans[arr[j].No] = query(BIT, arr[j].y);
		}

		//	Update
		for(int j=i;j<endIdx;j++){
			update(arr[j].y, BIT, maxBitvalue);
		}

		i = endIdx;
	}
	
	delete []ans;
	delete []arr;
	delete []BIT;
	return 0;
}