#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <cmath>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define ll long long


int getCount2(int sz,int len)
{
	return pow(sz, len);
}

int getCount(int sz,int len)
{
	if(len == 0 || sz == 0) return 0;
	if(sz == 1) return sz*len;
	return (sz * (pow(sz, len) - 1))/(sz - 1);
}



int atMostGivenDigitSet(vector<string> &digits, int n)
{
	if(digits.size() == 0) return 0;
	int len = 0, temp = n;
	string value = "";
	while(temp > 0){
		value = char(temp%10 + '0') + value;
		temp /= 10;
		len++;
	}
	string v2 = "";
	int ans = getCount(digits.size(), len - 1);
	for(int i = 0;i < value.size();i++){

		bool check = false;
		for(string &c: digits){
			if(c[0] < value[i]){
				ans += getCount2(digits.size(), len - i - 1);
			}
			else if(c[0] == value[i]){
				check = true;
				v2 += c[0];
			}
		}

		if(!check) break;
	}

	return ans + (v2 == value?1:0);
}

int main(){
	int sz, n;
	cin >> sz;
	vector<string> digits(sz);
	for(string &s: digits) cin >> s;
	cin >> n;
	cout << atMostGivenDigitSet(digits, n) << "\n";
	return 0;
}

