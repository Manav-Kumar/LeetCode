#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>

bool compare(pair<int,int> a, pair<int,int> b){
	return int(a.second - a.first) < int(b.second - b.first);
}


bool NonOverlap(vector<pair<int,int> > &chosenIntervals,pair<int,int> &a){
	for(pair<int,int> &b: chosenIntervals){
		if(b.second < a.first || b.first > a.second) continue;
		else return false;
	}
	return true;
}


vector<string> maxNumOfSubstrings(string s){
	int n = s.size();
	vector<pair<int,int> > intervals(26, {-1, n + 1});
	for(int i = 0;i<n;i++){
		int index = int(s[i] - 'a');
		if(intervals[index].first == -1) intervals[index] = {i,i};
		else intervals[index].second = i;
	}


	for(int i = 0;i < 26;i++){
		if(intervals[i].first == -1) continue;

		//	Expanding the intervals
		int start = intervals[i].first, end = intervals[i].second;
		stack<pair<int,int> > k;
		k.push(pair<int,int> (start, end));
		while(k.size() > 0){
			int cur_s = k.top().first, cur_e = k.top().second; 
			k.pop();
			for(int index = cur_s;index <= cur_e;index++){
				int new_s = intervals[s[index] - 'a'].first, new_e = intervals[s[index] - 'a'].second;

				if(new_s < start) k.push({new_s, start - 1}), start = new_s;
				if(new_e > end) k.push({end + 1, new_e}), end = new_e;
			}
		}


		intervals[i] = {start, end};
	}

	
	sort(intervals.begin(), intervals.end(), compare);

	vector<string> res;
	// vector<bool> visited(n, false);

	// for(int i=0;i<intervals.size();i++){
	// 	if(intervals[i].first == -1) return res;
	// 	string d = "";
	// 	for(int index = intervals[i].first;index <= intervals[i].second;index++){
	// 		if(visited[index]){
	// 			d = ""; break;
	// 		}
	// 		d += s[index];
	// 	}

	// 	if(!d.empty()){
	// 		res.push_back(d);
	// 		for(int index = intervals[i].first;index<=intervals[i].second;index++) visited[index] = true;
	// 	}
	// }

	vector<pair<int,int> > chosenIntervals;
	for(int i=0;i<26;i++){
		if(intervals[i].first == -1) return res;
		if(NonOverlap(chosenIntervals, intervals[i])){
			chosenIntervals.push_back(intervals[i]);
			res.push_back(s.substr(intervals[i].first, intervals[i].second - intervals[i].first + 1));
		}
	}

	return res;
}



int main(){
	string s;
	cin >> s;
	vector<string> ans = maxNumOfSubstrings(s);
	for(string &s: ans) cout << s << "\n";
	return 0;
}







