#include<iostream>
#include <vector>
#include <queue>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>


void restoreIpAddresses(string s,vector<string> &ret, string ans = "",int ct = 0){

	if(ct > 4) return;
	if(s.empty()){
		if(ct == 4) ret.push_back(ans);
		return;
	}
	int curr = 0;
	for(int i=0;i<s.size();i++){
		if(i > 0 && curr == 0) return;
		curr = curr*10 + int(s[i] - '0');
		if(curr > 255) return;
		restoreIpAddresses(s.substr(i + 1), ret, (ans.empty()?"":ans + '.') + s.substr(0, i + 1), ct + 1);
	}
}

vector<string> restoreIpAddresses(string s){
	vector<string> ret;
	restoreIpAddresses(s, ret);
	return ret;
}

//	Additive Number

bool isFibo(long long a,long long b,string &num, int idx, bool check = false){

	if(idx == num.size()) return check;

	long long curr = 0;
	for(int i = idx;i < num.size();i++){

		if(i > idx && curr == 0) return false;
		curr = curr*10 + int(num[i] - '0');
		if(curr == (a + b)) return isFibo(b, curr, num, i + 1, true);
		else if(curr > (a + b)) return false;
	}
	return false;
}

bool isAdditiveNumber(string num){
	//	Choosing first 2 digits
	long long a = 0, b = 0;
	for(int i=0;i<num.size();i++){
		if(i > 0 && a == 0) return false;
		a = a*10 + int(num[i] - '0'), b = 0;
		for(int j = i+1;j<num.size();j++){
			if(j > i + 1 && b == 0) break;
			b = b*10 + int(num[j] - '0');
			if(isFibo(a, b, num, j + 1)) return true;
		}
	}

	return false;
}

bool isFibo(long long a,long long b,string &num, int idx,vector<int> &ans){

	if(idx == num.size()) return true;

	long long curr = 0;
	for(int i = idx;i < num.size();i++){

		if(i > idx && curr == 0) return false;
		curr = curr*10 + int(num[i] - '0');
		if(curr > INT_MAX) return false;
		if(curr == (a + b)){
			ans.push_back(curr);
			bool check = isFibo(b, curr, num, i + 1, ans);
			if(!check) ans.pop_back();
			return check;
		}
		else if(curr > (a + b)) return false;
	}
	return false;
}

vector<int> splitIntoFibonacci(string num){

	vector<int> ans;
	long long a = 0, b = 0;
	for(int i=0;i<num.size();i++){
		if(i > 0 && a == 0) return vector<int> ();
		a = a*10 + int(num[i] - '0'), b = 0;
		if(a > INT_MAX) return vector<int> ();
		ans.push_back(a);
		for(int j = i+1;j<num.size();j++){
			if(j > i + 1 && b == 0) break;
			b = b*10 + int(num[j] - '0');
			if(b > INT_MAX) break;
			ans.push_back(b);
			if(isFibo(a, b, num, j + 1, ans) && ans.size() > 2) return ans;
			ans.pop_back();
		}
		ans.pop_back();
	}

	return ans;
}

int main(){
	string num;
	cin >> num;
	vector<int> ans = splitIntoFibonacci(num);
	for(int &a: ans) cout << a << "\n";
	return 0;
}





