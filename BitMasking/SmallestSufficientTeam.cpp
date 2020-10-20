#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <cmath>
#include <math.h>
#include <unordered_set>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vector<int> >
#define vvb vector<vector<bool> >
#define vs vector<string>
#define vvs vector<vs>
#define ull unsigned long long
#define vull vector<ull> 
#define vvull vector<vull>
#define vp vector<pair<int,ull> >
#define vvp vector<vp>

#define MAX_VALUE ((ull)1<<63) - 1

int getSize(ull value)
{
	int ones = 0;
	while(value > 0){
		if((value&1) > 0) ones++;
		value = (value>>1);
	}
	return ones;
}

// vector<vector<pair<ull,int> > > visited;
// map<string,int> mp;

// pair<ull,int> helper(vector<int> arr,int mask,int allmask, int idx = 0){

// 	if(mask == allmask) return pair<ull,int> (0,0);
// 	if(idx == arr.size()) return pair<ull,int> (MAX_VALUE, 100);
// 	if(visited[idx][mask].second != 100) return visited[idx][mask];
// 	pair<ull,int> a1 = helper(arr, mask, allmask, idx + 1);
// 	pair<ull,int> a2 = helper(arr, mask | arr[idx], allmask, idx + 1);
// 	a2.first |= ((ull)1<<idx);
// 	a2.second += 1;


// 	pair<ull,int> ans = a1.second < a2.second? a1:a2; 
// 	visited[idx][mask] = ans;
// 	return ans;

// }

// vector<int> smallestSufficientTeam(vector<string> &req_skills, vector<vector<string> > &people)
// {
// 	int total = req_skills.size(), allmask = (1<<total)-1;
// 	for(int i=0;i<total;i++) mp[req_skills[i]] = i;

// 	vector<int> arr(people.size(), 0);
// 	for(int i=0;i<people.size();i++){
// 		int& value = arr[i];
// 		for(string &s: people[i]){
// 			value |= (1 << mp[s]);
// 		}
// 	}

// 	visited.assign(people.size(), vector<pair<ull,int> >(1<<total, pair<ull,int>(MAX_VALUE, 100)));


// 	pair<ull,int> temp = helper(arr, 0, allmask);
// 	ull ans = temp.first;
// 	vector<int> ret;
// 	for(int i=0;i<people.size();i++){
// 		if(((ans>>i)&1) > 0) ret.push_back(i);
// 	}

// 	return ret;
// }




vector<vector<ull> > visited;
map<string,int> mp;

ull helper(vector<int> arr,int mask,int allmask,int idx = 0){

	if(mask == allmask) return 0;
	if(idx == arr.size()) return MAX_VALUE;

	if(visited[idx][mask] != MAX_VALUE) return visited[idx][mask];
	ull a1 = helper(arr, mask, allmask, idx + 1);
	ull a2 = helper(arr, mask | arr[idx], allmask, idx + 1);
	a2 |= ((ull)1<<idx);


	ull ans = getSize(a1) < getSize(a2)?a1:a2; 
	visited[idx][mask] = ans;
	return ans;

}

vector<int> smallestSufficientTeam(vector<string> &req_skills, vector<vector<string> > &people)
{
	int total = req_skills.size(), allmask = (1<<total)-1;
	for(int i=0;i<total;i++) mp[req_skills[i]] = i;

	vector<int> arr(people.size(), 0);
	for(int i=0;i<people.size();i++){
		int& value = arr[i];
		for(string &s: people[i]){
			value |= (1 << mp[s]);
		}
	}

	visited.assign(people.size(), vector<ull> (allmask, MAX_VALUE));

	ull ans = helper(arr, 0, allmask);
	vector<int> ret;
	for(int i=0;i<people.size();i++){
		if(((ans>>i)&1) > 0) ret.push_back(i);
	}

	return ret;
}





// vector<vector<ull>> memo;
// map<string,int> mp;
// ull dp(int mask,int person,int allmask,vector<int> people)
// {
//     if(mask==allmask)
//         return 0;
//     if(person>=people.size())
//         return MAX_VALUE;
//     if(memo[mask][person]!=MAX_VALUE)
//         return memo[mask][person];


//     ull a1 = dp(mask|people[person],person+1,allmask,people);
//     ull a2 = dp(mask,person+1,allmask,people);
//     a1 |= ((ull)1<<person);

//     ull ans = getSize(a1) < getSize(a2)? a1:a2;
//     memo[mask][person]=ans;
//     return ans;
// }


// vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& p) 
// {
//     vector<int> people(p.size(),0);
//     int allmask=(1<<req_skills.size())-1;
//     memo.assign(allmask+1, vector<ull>(people.size(), MAX_VALUE));
//     for(int i=0;i<req_skills.size();i++)
//         mp[req_skills[i]]=i;
//     for(int i=0;i<p.size();++i)
//     {
//         int mask=0;
//         for(string skill:p[i])
//             mask=mask|(1<<mp[skill]);
//         people[i]=mask;
//     }
//     vector<int> ret;
//     ull val = dp(0,0,allmask,people);
//     for(int i=0;i<p.size();i++){
//     	if(((val>>i)&1) > 0) ret.push_back(i);
//     }

//     return ret;
// }


// vector<vector<ull>> memo;
// map<string,int> mp;
// ull dp(int mask,int person,int allmask,vector<int> people)
// {
//     if(mask==allmask)
//         return 0;
//     if(person>=people.size())
//         return MAX_VALUE;
//     if(memo[mask][person]!=MAX_VALUE)
//         return memo[mask][person];
//     ull a1 = dp(mask|people[person],person+1,allmask,people);
//     ull a2 = dp(mask,person+1,allmask,people);
//     a1 |= ((ull)1<<person);
//     memo[mask][person] = getSize(a1) < getSize(a2)?a1:a2;
//     return memo[mask][person];
// }

// vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& p) 
// {
//     vector<int> people(p.size(),0);
//     int allmask=(1<<req_skills.size())-1;
//     memo.resize(allmask, vector<ull>(people.size(), MAX_VALUE));
//     for(int i=0;i<req_skills.size();++i)
//         mp[req_skills[i]]=i;
//     for(int i=0;i<p.size();++i)
//     {
//         int mask=0;
//         for(string skill:p[i])
//             mask=mask|1<<mp[skill];
//         people[i]=mask;
//     }
//     vector<int> ret;
//     ull val=dp(0,0,allmask,people);
//     for(int person=0;person<people.size();++person)
//     {
//     	if(((val>>person)&1) > 0) ret.push_back(person); 
//     }
//     return ret;
// }


int main(){
	int n, m;
	cin >> n;
	vector<string> req_skills(n);
	for(string &s: req_skills) cin >> s;
	cin >> m;
	vector<vector<string> > people(m);
	for(vector<string> &tsd: people){
		int g;
		cin >> g;
		tsd.assign(g,"");
		for(string &s: tsd) cin >> s;
	}
	vi ans = smallestSufficientTeam(req_skills, people);
	for(int &a: ans) cout << a << " ";
	return 0;
}


