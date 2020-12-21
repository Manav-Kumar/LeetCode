#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <random>
using namespace std;

#define vi vector<int>

class It{
	int data;
	void temp(){
		cout << "It\n";
	}
	friend class Pt;
};

class Pt: public It{
public:
	void temp(){
		this->It::temp();
		cout << "Pt\n";
	}
};


class CombinationIterator{
	string s;
	int len, idx = 0;
	vector<string> finalans;

	void Recurr(string ans, int start,int len){
		if(len == 0) finalans.push_back(ans);
		else if(start >= s.size()) return;
		else{
			for(int i = start;i < s.size();i++){
				Recurr(ans + s[i], i + 1, len - 1);
			}
		}
	}

public:
	CombinationIterator(string s, int len): s(s), len(len), idx(0) {
		Recurr("", 0, len);
	}

	string next(){
		return finalans[idx++];
	}

	bool hasNext(){
		if(idx < finalans.size()) return true;
		else return false;
	}

};

int main(){
	string s;
	int len;
	cin >> s >> len;
	CombinationIterator cit(s, len);
	for(int i=0;i<3;i++){
		cout << cit.hasNext() << " ";
		cout << cit.next() << "\n";
	}
	cout << cit.hasNext() << "\n";
	return 0;
}


