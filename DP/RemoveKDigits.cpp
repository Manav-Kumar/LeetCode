#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define ll long long

string removeKDigits(string num,int k)
{
	stack<char> s;
	int i = 0;
	for(;i<num.size();i++){
		if(k == 0) break;
		if(!s.empty() && s.top() > num[i] && k > 0){
			s.pop();
			k--;
		}
		s.push(num[i]);
	}
	string ans = "";
	while(!s.empty()){
		ans = s.top() + ans;
		s.pop();
	}
	while(i < num.size() && num[i] == '0') i++;
	while(i < num.size()){
		ans += num[i++];
	}
	return ans;
}

int main(){
	string num;
	cin >> num;
	int k;
	cin >> k;
	cout << removeKDigits(num, k) << "\n";
	return 0;
}

