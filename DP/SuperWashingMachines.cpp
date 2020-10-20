#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <cmath>
using namespace std;

#define vi vector<int> 
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vmp vector<map<int,int> >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvmp vector<vmp>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define ll long long

ll mod = 1e9 + 7;

int findMinMoves(vi &machines)
{
	int totalDresses = 0, N = machines.size();
	for(int &a: machines) totalDresses += a;

	if(totalDresses%N != 0) return -1;
	
	int goal = totalDresses/N, maxDress = 0, current = 0;

	for(int &dress: machines){
		current += (goal - dress);
		maxDress = max(abs(current), maxDress);//	This is for those whose dress < goal
		maxDress = max((goal - dress), maxDress);//	This is for those whose dress > goal
	}

	return maxDress;
}

//	Number Of Paths With MaxScore

int getWays(vector<string> &board,int i,int j,int sum, vvvi &store)
{
	int n = board.size(), m = board[0].size();
	if(i == 0 && j == 0){
		return sum == 0;
	}
	if(i < 0 || j < 0 || board[i][j] == 'X' || sum < 0) return 0;
	int &finalAns = store[i][j][sum];
	if(finalAns != -1) return finalAns;
	sum -= ((i == n-1 && j == m-1)?0:board[i][j] - '0');
	int ans = getWays(board, i, j-1, sum, store);
	ans += getWays(board, i-1, j, sum, store);
	ans += getWays(board, i-1, j-1, sum, store);
	finalAns = ans;
	return ans;
}

vi pathsWithMaxScore(vector<string> &board)
{
	int n = board.size(), m = board[0].size();
	vvi dp(n, vi(m, -1));
	dp[0][0] = 0;
	for(int j = 1;j < m;j++){
		if(board[0][j] == 'X') break;
		dp[0][j] = dp[0][j - 1] + (board[0][j] - '0');
	}
	for(int i = 1;i < n;i++){
		if(board[i][0] == 'X') break;
		dp[i][0] = dp[i - 1][0] + (board[i][0] - '0');
	}
	for(int i = 1;i < n;i++){
		for(int j = 1;j < m;j++){
			if(board[i][j] == 'X') continue;

			int ans = max({dp[i][j-1], dp[i-1][j], dp[i-1][j-1]});

			if(ans != -1) dp[i][j] = ans + (i == n-1 && j == m-1? 0:(board[i][j] - '0'));
		}
	}

	if(dp[n-1][m-1] == -1) return vi {0, 0};

	int sum = dp[n-1][m-1];
	vvvi store(n, vvi(m, vi(sum + 1, -1)));
	int count = getWays(board, n - 1, m - 1, sum, store);
	
	return vi{sum, count};

}


vi pathsWithMaxScore2(vector<string> &board)
{
	int n = board.size(), m = board[0].size();
	vvpii dp(n, vpii(m, pair<int,int> (0, 0)));
	
	dp[0][0] = pair<int,int> (0, 1);
	for(int j = 1;j < m;j++){
		if(board[0][j] == 'X') break;
		int sum = dp[0][j-1].first + (board[0][j] - '0');
		dp[0][j] = pair<int,int> (sum, 1);
	}

	for(int i = 1;i < n;i++){
		if(board[i][0] == 'X') break;
		int sum = dp[i-1][0].first + (board[i][0] - '0');
		dp[i][0] = pair<int,int> (sum, 1);
	}

	for(int i = 1;i < n;i++){
		for(int j = 1;j < m;j++){
			if(board[i][j] == 'X') continue;
			int &sum = dp[i][j].first;
			int &count = dp[i][j].second;

			sum = max({dp[i][j-1].first, dp[i-1][j-1].first, dp[i-1][j].first});

			if(sum == dp[i][j-1].first) count += dp[i][j-1].second;

			if(sum == dp[i-1][j-1].first) count += dp[i-1][j-1].second;

			if(sum == dp[i-1][j].first) count += dp[i-1][j].second;

			if(sum != 0) dp[i][j].first += (i == n-1 && j == m-1 ?0:(board[i][j] - '0'));

		}
	}

	return vi {dp[n-1][m-1].first, dp[n-1][m-1].second};
}


vi pathsWithMaxScore3(vector<string> &board)
{
	int n = board.size(), m = board[0].size();

	vvpii dp2(n, vpii(m, pair<int,int> (0, 0)));
	
	dp2[0][0] = pair<int,int> (0, 1);
	for(int j = 1;j < m;j++){
		if(board[0][j] == 'X') break;
		int sum = dp2[0][j-1].first + (board[0][j] - '0');
		dp2[0][j] = pair<int,int> (sum, 1);
	}

	for(int i = 1;i < n;i++){
		if(board[i][0] == 'X') break;
		int sum = dp2[i-1][0].first + (board[i][0] - '0');
		dp2[i][0] = pair<int,int> (sum, 1);
	}

	for(int i = 1;i < n;i++){
		for(int j = 1;j < m;j++){
			if(board[i][j] == 'X') continue;
			int &sum = dp2[i][j].first;
			int &count = dp2[i][j].second;

			sum = max({dp2[i][j-1].first, dp2[i-1][j-1].first, dp2[i-1][j].first});

			if(sum == dp2[i][j-1].first) count += dp2[i][j-1].second;

			if(sum == dp2[i-1][j-1].first) count += dp2[i-1][j-1].second;

			if(sum == dp2[i-1][j].first) count += dp2[i-1][j].second;

			if(sum != 0) dp2[i][j].first += (i == n-1 && j == m-1 ?0:(board[i][j] - '0'));

		}
	}

	//return vi {dp[n-1][m-1].first, dp[n-1][m-1].second};


	vvpii dp(2, vpii(m, pair<int,int> (0, 0)));
	
	dp[0][0] = pair<int,int> (0, 1);

	for(int j = 1;j < m;j++){
		if(board[0][j] == 'X') break;
		int sum = dp[0][j-1].first + (board[0][j] - '0');
		dp[0][j] = pair<int,int> (sum, 1);
	}

	vpii ZrCol(n, pair<int,int> (0,0));
	ZrCol[0] = pair<int,int> (0,1);

	for(int i = 1;i < n;i++){
		if(board[i][0] == 'X') break;
		int sum = ZrCol[i-1].first + (board[i][0] - '0');
		ZrCol[i] = pair<int,int> (sum, 1);
	}

	int current = 1;

	for(int i = 1;i < n;i++){
		for(int j = 1;j < m;j++){
			int &sum = dp[current][j].first;
			int &count = dp[current][j].second;
			sum = 0, count = 0;
			if(board[i][j] == 'X') continue;
			pair<int,int> up = dp[current^1][j];
			pair<int,int> upleft, left;

			if(j == 1){
				left = ZrCol[i], upleft = ZrCol[i-1];
			}
			else{
				left = dp[current][j-1], upleft = dp[current^1][j-1];
			}

			sum = max({left.first, upleft.first, up.first});

			if(sum == left.first) count += left.second;

			if(sum == upleft.first) count += upleft.second;

			if(sum == up.first) count += up.second;

			if(sum != 0){
				dp[current][j].first += ((i == n-1 && j == m-1 )?0:(board[i][j] - '0'));
			}

			if(dp[current][j] != dp2[i][j]){
				cout << i << " " << j << "\n";
				cout << dp[current][j].first << " " << dp[current][j].second << "\n";
				cout << dp2[i][j].first << " " << dp2[i][j].second << "\n\n"; 
			}

		}
		current ^= 1;
	}


	return vi {dp[current^1][m-1].first, dp[current^1][m-1].second};
}

int main(){
	int n;
	cin >> n;
	vector<string> board(n);
	for(string &s: board) cin >> s;
	vector<int> ans = pathsWithMaxScore3(board);
	cout << ans[0] << " " << ans[1] << "\n";
	return 0;
}

