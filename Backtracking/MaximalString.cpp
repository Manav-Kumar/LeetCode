#include <iostream>
using namespace std;


void solve(string a,int b,string &ret,int idx = 0){

	if(b == 0 ||idx == a.size()){
		ret = max(ret, a);
		return;
	}

	for(int i = idx + 1;i < a.size();i++){
		if(a[idx] >= a[i]) continue;

		swap(a[idx], a[i]);
		solve(a, b - 1, ret, idx + 1);
		swap(a[idx], a[i]);
	}
	solve(a, b, ret, idx + 1);
}


int main(){
	string a;
	int b;
	cin >> a >> b;
	string ret = a;
	solve(a, b, ret);
	cout << ret << "\n";
	return 0;
}


