#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>


string reverseWords(string s){
	string ans = "", curr = "";
	for(char &c: s){
		if(c == ' '){
			if(curr.size() > 0) ans = curr + ans;
			curr = ""; continue;
		}
		else curr += c;
	}

	if(curr.size() > 0) ans = curr + ans;
	return ans;
}



vector<string> split(string t, char delimiter){
	vector<string> elems;
	string curr = ""; int j = 0, z = 4;

	while(z--){
		while(j < t.size() && t[j] != '\0' && t[j] != ',') curr += t[j++];
		elems.push_back(curr), curr = "", j++;
	}

	return elems;
}

vector<string> invalidTransactions(vector<string> &transactions){

	int n = transactions.size();
	unordered_set<string> res;
	unordered_map<string, vector<int> > m;
	vector<bool> invalid(n, false);

	for(int i=0;i<n;i++){
		vector<string> transaction = split(t, ',');
		string name = transaction[0], city = transaction[3];
		int time = stoi(transaction[1]), amount = stoi(transaction[2]);

		if(stoi(amount) > 1000) invalid[i] = true;

		for(auto info: m[name]){
			if(info[3] != city && abs(stoi(info[1]) - stoi(time)) <= 60){
				res.insert(info[0] + "," + info[1] + "," + info[2] + "," + info[3]);
				if(res.count(t) == 0) res.insert(t);
			}
		}

		m[name].push_back({name, time, amount, city});
	}

	vector<string> ans;
	for(string k: res) ans.push_back(k);

	return ans;
}

class info{
public:
	string name, city, time, amount;
	info(string n, string t, string a, string c): name(n), time(t), amount(a), city(c) {}
};

bool compare(info &a, info &b){
	return stoi(a.time) <= stoi(b.time);
}

vector<string> invalidTransactions2(vector<string> &transactions){
	int n = transactions.size();
	vector<info> arr;
	for(string &t: transactions){
		vector<string> transaction = split(t, ',');
		arr.push_back({transaction[0], transaction[1], transaction[2], transaction[3]});
	}

	sort(arr.begin(), arr.end(), compare);

	unordered_set<string> res;

	unordered_map<name, vector<string> > lastsixty;

	for(int i=0;i<n;i++){
		for(int j = i-1;j >= 0 && abs(stoi(arr[i].time) - stoi(arr[j].time)) <= 60;j--){
			if(arr[i].name == arr[j].name && arr[i].city != arr[j].city){
				res.insert(arr[i].name + "," + arr[i].time + "," + arr[i].amount + "," + arr[i].city);
				res.insert(arr[j].name + "," + arr[j].time + "," + arr[j].amount + "," + arr[j].city);
			}
		}
	}



	vector<string> ans;
	for(string k: res) ans.push_back(k);

	return ans;
}

int main(){
	return 0;
}





