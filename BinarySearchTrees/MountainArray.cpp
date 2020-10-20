#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <list>
using namespace std;

#define vb vector<bool>
#define vi vector<int>
#define vvb vector<vb>
#define vvi vector<vi>

class MountainArray{
public:
	int size;
	int *arr;
	MountainArray(int n){
		arr = new int[n];
		size = n;
	}
	~MountainArray(){
		delete []arr;
	}

	int get(int index){
		return arr[index];
	}
	int length(){
		return size;
	}
};

int findInMountainArray(int target,MountainArray &mountainArr){
	int n = mountainArr.length(), st = 0, en = n-1, index = -1, ans = -1;

	while((en - st) >= 2){
		int mid = (st + en)/2;
		index = mid;
		int v1 = mountainArr.get(mid), v2 = mountainArr.get(mid + 1);
		if(v2 > v1){
			st = mid;
		}
		else if(v1 > v2){
			en = mid;
		}
	}

	cout << index << "\n";

	st = 0, en = index;
	while(st <= en){
		int mid = (st + en)/2;
		int value = mountainArr.get(mid);
		if(value == target) ans = mid;
		if(target <= value){
			en = mid - 1;
		}
		else st = mid + 1;
	}

	if(ans != -1) return ans;

	st = index, en = n-1;
	while(st <= en){
		int mid = (st + en)/2;
		int value = mountainArr.get(mid);
		if(value == target) ans = mid;
		if(target >= value){
			en = mid - 1;
		}
		else st = mid + 1;
	}

	return ans;
}

int main(){
	int n, target;
	cin >> n;
	MountainArray mountainArr(n);
	for(int i=0;i<n;i++) cin >> mountainArr.arr[i];
	cin >> target;
	cout << findInMountainArray(target, mountainArr) << "\n";
	return 0;
}


