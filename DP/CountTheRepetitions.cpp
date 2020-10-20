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

int getMaxRepetitions(string s1, int n1,string s2,int n2)
{
	int p1 = 0, p2 = 0, mark = 0;
	while(p1 < s1.size()*n1){
		char c = s2[p2%s2.size()];
		while(s1[p1%s1.size()] != c && p1 < (s1.size()*n1)) p1++;
		p2++, p1++;
		if(p2%s2.size() == 0){
			if(p2 == s2.size()){
				mark = p1;//	Put marker for the p1 where s2 first time ends
			}
			else if(p1%s1.size() == mark%s1.size()){
				//Repeated Cycle started to appear
				int round = (s1.size()*n1 - p1)/(p1 - mark);
				p1 += round*(p1 - mark);
				p2 += round*(p2 - s2.size());
			}
		}
	}

	return p2/s2.size()/n2;
}

int main(){

	return 0;
}