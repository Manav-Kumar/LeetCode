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
#define f first
#define s second

int Distance(int prev,int curr)
{
	prev--, curr--;
	pair<int,int> p(prev/6, prev%6);
	pair<int,int> c(curr/6, curr%6);
	return abs(p.f - c.f) + abs(p.s - c.s);
}

int helper(string word,map<char,int >& alpa,int ***dp,int l,int r)
{
	int n = word.size();
	if(word.empty()) return 0;
	if(dp[n][l][r] != -1) return dp[n][l][r];
	int a1 = helper(word.substr(1), alpa, dp, alpa[word[0]], r);
	if(l != 0) a1 += Distance(l,alpa[word[0]]);

	int a2 = helper(word.substr(1), alpa, dp, l, alpa[word[0]]);
	if(r != 0) a2 += Distance(alpa[word[0]], r);
	int ans = min(a1, a2);
	if(dp[n][l][r] != -1) dp[n][l][r] = ans;
	return ans;
}


map<char,pair<int,int> > mp;
int dp[7][7][7][7][301];
int dfs(string word, pair<int,int> finger1, pair<int,int> finger2, int currIndex,int len){
    if(currIndex == len){
        return 0;
    }
    // cout << currIndex << endl;
    int x1 = finger1.first;
    int x2 = finger2.first;
    int y1 = finger1.second;
    int y2 = finger2.second;
    if(dp[x1][y1][x2][y2][currIndex] != -1){
        return dp[x1][y1][x2][y2][currIndex];
    }
    pair<int,int> curr_p = mp[word[currIndex]];
    int curr_x = curr_p.first;
    int curr_y = curr_p.second;
    int dist1 = abs(x1-curr_x) + abs(y1-curr_y);
    int dist2 = abs(x2-curr_x) + abs(y2-curr_y);
    return dp[x1][y1][x2][y2][currIndex] = min(dist1 + dfs(word,curr_p,finger2,currIndex+1,len), 
               dist2 + dfs(word,finger1,curr_p,currIndex+1,len));
}
int minimumDistance(string word) {
    int len = word.length();
    char ch = 'A';
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
            mp[ch] = make_pair(i,j);
            ch++;
            if(i==4 && j==2){
                break;
            }
        }
    }
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            for(int k=0;k<7;k++){
                for(int l=0;l<7;l++){
                    for(int m=0;m<301;m++){
                        dp[i][j][k][l][m] = -1;
                    }
                }
            }
        }
    }
    pair<int,int> finger1 = make_pair(1,1);
    pair<int,int> finger2 = make_pair(0,0);
    char firstChar = word[0];
    finger1 = mp[firstChar];
    int minCost = INT_MAX;
    for(int j=1;j<len;j++){
        finger2 = mp[word[j]];
        minCost = min(minCost,dfs(word,finger1,finger2,0,len));
    }
    return minCost == INT_MAX? 0: minCost;
}

int main()
{
	string word;
	cin >> word;
	cout << minimumDistance(word) << "\n";
	map<char,int> alpa;
	int col = 1;
	for(int i=0;i<26;i++)
	{
		char c = (i + 'A');
		alpa[c] = col;
		col++;
	}
	int ***dp = new int**[word.size()+1];
	for(int i=0;i<=word.size();i++)
	{
		dp[i] = new int*[32];
		for(int j=0;j<32;j++)
		{
			dp[i][j] = new int[32];
			fill(dp[i][j], dp[i][j] + 32, -1);
		}
	}
	char firstChar = word[0];
    int finger1 = alpa[firstChar];
    int minCost = INT_MAX;
    for(int j=1;j<word.size();j++){
        int finger2 = alpa[word[j]];
        minCost = min(minCost,helper(word,alpa, dp, finger1,finger2));
    }
    cout <<  (minCost == INT_MAX? 0: minCost) << "\n";
	for(int i=0;i<=word.size();i++)
	{
		for(int j=0;j<32;j++) delete []dp[i][j];
		delete []dp[i];
	}
	delete []dp;
	return 0;
}
