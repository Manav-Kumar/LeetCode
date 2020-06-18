#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <queue>
using namespace std;
int main()
{
	map<string,int> mp;
	mp["va"] = 1;
	mp["wf"] = 3;
	if(mp.find("wf") != mp.end()) cout << "ok ";
}