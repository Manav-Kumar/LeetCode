#include <iostream>
#include <vector>
using namespace std;

//	Negation means taking only 1's complement, while taking -ve of pos number in computer means it is going to 
//			take 2's complement of it

//	Start Implementing fenwick tree for array sum problem
int query(int *BIT,int index)
{
	int sum = 0;
	for(;index > 0;index -= (index&(-index))){
		sum += BIT[index];
	}
	return sum;
}

void update(int *BIT,int index,int value,int n){

	for(;index <= n;index += (index&(-index))){
		BIT[index] += value;
	}
}


int main(){
	int n;
	int *arr = new int[n + 1];
	int *BIT = new int[n+1]();
	for(int i=1;i<=n;i++){
		cin >> arr[i];
		update(BIT, i, arr[i], n);
	}	
	int x = ~6;
	if((x>>4)&1) cout << "ok\n";
	else cout << "not ok\n";
	cout << (6&(-6)) << "\n";
	return 0;
}


