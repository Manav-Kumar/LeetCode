#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <set>
using namespace std;

//	Given 2 strings find the no of operations of req. on a to make it equal to b

int NoOperations(string a,string b)
{
	int cost = 0, i = 0;
	while(i < a.size()){
		if(a[i] == b[i]) i++;
		else if(i+1 < a.size() && a[i+1] != b[i+1] && a[i] != a[i+1]){
			cost++;
			i += 2;
		}
		else{
			cost++;
			i += 1;
		}
	}
	return cost;
}

int lightBulb(string s, long long x,long long y){
	int count = 0, i = 0;
	bool prev = false, allones = true;
	while(i < s.size()){
		if(s[i] == '1'){
			if(prev){
				count++;
				prev = false;
			}
		}
		if(s[i] == '0'){
			prev = true;
			allones = false;
		}
		i++;
	}
	if(!prev) count--;
	if(count <= 0){
		if(allones) return 0;
		count = 0;
	}
	return count*min(x,y) + y;
}

void circularStudents(){
	int t, i, p;
	cin >> t;
	while(t--){
		cin >> i >> p;
		i += p;
		cout << i%12 << "\n";
	}
}

int interestingSeq(int *arr,int n,int k,int l){
	sort(arr, arr + n);
	int *helper = new int[n];
	helper[0] = arr[0];
	for(int i=1;i<n;i++) helper[i] = helper[i-1] + arr[i];

	int ans = INT_MAX, index = 0;
	for(int possibleValues = arr[0];possibleValues <= arr[n-1];possibleValues++){

		// int i = 0, inc = 0, dec = 0;
		// while(i < n && arr[i] <= possibleValues){
		// 	inc += possibleValues - arr[i++];
		// }
		// i = n-1;
		// while(i >= 0 && arr[i] >= possibleValues){
		// 	dec += (arr[i--] - possibleValues);
		// }

		while(index < n && arr[index] <= possibleValues) index++;
		int inc = possibleValues*index;
		int dec = helper[n-1] - possibleValues*(n - index);
		if(index - 1 >= 0){
			inc -= helper[index-1];
			dec -= helper[index-1];
		}
		if(dec <= inc){
			int cost = dec*k + (inc - dec)*l;
			ans = min(ans, cost);
		}
	}
	delete []helper;
	return ans;
}

void winningStrategy(){
	int n, fs = 0;
	cin >> n;
	int *players = new int[n + 1];
	for(int i=0;i<n;i++) cin >> players[i];

	for(int i = n-1;i >= 0;i--){
		if(players[i] == i+1) continue;
		else if(i-1 >= 0 && players[i-1] == i + 1){
			players[i - 1] = players[i];
			players[i] = i + 1;
			fs++;
		}
		else if(i - 2 >= 0 && players[i - 2] == i+1){
			players[i-2] = players[i-1];
			players[i-1] = players[i];
			players[i] = i + 1;
			fs += 2;
		}
		else{
			cout << "NO\n";
			return; 
		}
	}

	cout << "YES\n" << fs << "\n";
	return;

}


int main(){
	winningStrategy();
	return 0;
}

