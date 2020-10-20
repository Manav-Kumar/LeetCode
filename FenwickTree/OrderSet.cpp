#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Questions{
public:
	char c;
	int index;
};

int query(int *BIT,int index){

	int sum = 0;
	for(;index > 0;index -= (index&(-index))){
		sum += BIT[index];
	}
	return sum;
}

void update(int *BIT,int index,int n,int value){

	for(;index <= n;index += (index&(-index))){
		BIT[index] += value;
	}
}

void findKthSmallest(int *BIT,int k,int st,int en,map<int,int> revMp)
{
	int lo = st, hi = en;
	while(lo <= hi){
		int mid = (lo + hi)/2;
		int value = query(BIT, mid);
		if(value == k && query(BIT, mid - 1) != value){
			cout << revMp[mid] << "\n";
			return;
		}
		else if(k <= value){
			hi = mid - 1;
		}
		else lo = mid + 1;
	}
	cout << "invalid\n";
}


void findKthSmallest(int *BIT,int k,int st,int en)
{
	int lo = st, hi = en;
	while(lo <= hi){
		int mid = (lo + hi)/2;
		int value = query(BIT, mid);
		if(value == k && query(BIT, mid -1) != k){
			cout << mid << "\n";
			return;
		}
		else if(k <= value) hi = mid - 1;
		else lo = mid + 1;
	}
	cout << "invalid\n";
}


void OrderSet(){
	int q, count = 1;
	vector<int> A;
	cin >> q;
	Questions *arr = new Questions[q];
	for(int i=0;i < q;i++){
		cin >> arr[i].c >> arr[i].index;
		if (arr[i].c == 'I' || arr[i].c == 'D') A.push_back(arr[i].index);
	}
	sort(A.begin(), A.end());
	map<int,int> mp;
	map<int,int> revMp;
	for(int count = 1;count <= A.size();count++){
		revMp[count] = A[count - 1];
		mp[A[count - 1]] = count;
	}

	int n = A.size();
	int *BIT = new int[n+1]();
	for(int i=0;i<q;i++){

		int value = arr[i].index;
		if(arr[i].c == 'I' && query(BIT, mp[value]) == query(BIT, mp[value] - 1)){
			update(BIT, mp[value], n, 1);
		}
		else if(arr[i].c == 'D' && query(BIT, mp[value]) != query(BIT, mp[value] - 1)){
			update(BIT, mp[value], n, -1);
		}
		else if(arr[i].c == 'K'){
			findKthSmallest(BIT, value, 1, n, revMp);
		}
		else if(arr[i].c == 'C'){
			//	Count of elements which are smaller than value
			auto j = lower_bound(A.begin(), A.end(), value);
			//	It gives you an iterator for the element which equal or just greater than it
			if(j == A.begin()){
				cout << 0;
			}
			else{
				j--;
				cout << query(BIT, mp[*j]) << "\n";
			}
		}
	}
	delete []arr;
	delete []BIT;
}

int main(){
	OrderSet();

	return 0;
}

