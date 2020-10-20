#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <unordered_map>
#include <set>
#include <cmath>
#include <math.h>
#include <unordered_set>
#include <climits>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repR(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define pb push_back
#define vb vector<bool>
#define vll vector<ll>
#define vi vector<int>
#define vvi vector<vi >
#define vpii vector<pair<int,int> >
#define vvpii vector<vpii>
#define vvb vector<vector<bool> >
#define vc vector<char>
#define vvc vector<vc>
#define vs vector<string>
#define vvs vector<vs>


string strWithout3a3b(int A,int B){

	string ans;
	int cta = 0, ctb = 0;
	while(A > 0 || B > 0){

		if(A >= B){
			if(cta != 2){
				ans += 'a', cta++, ctb = 0, A--;
			}
			else{
				ans += 'b', ctb++, cta = 0, B--;
			} 
		}
		else{
			if(ctb != 2){
				ans += 'b', ctb++, cta = 0, B--;
			}
			else{
				ans += 'a', cta++, ctb = 0, A--;
			}
		}
	}
	return ans;
}

//	Delete Columns To Make Sorted2
int minDeletionSize(vs &A){
	int len = A.size(), n = A[0].size(), ans = 0;
	vb visited(len, false);

	for(int c = 0;c < n;c++){
		vb temp = visited;
		bool check = true;
		for(int r = 1;r < len;r++){
			if(temp[r]) continue;
			if(A[r][c] > A[r - 1][c]) temp[r] = true;
			else if(A[r][c] < A[r - 1][c]){
				ans++, check = false; break;
			}
		}
		if(check){
			visited = temp;
		}
	}
	return ans;
}


//	Gas Station
int canCompleteCircuit(vi &gas, vi &cost){
	int n = gas.size();
    vi diff(n, 0);
    rep(i, 0, n) diff[i] = gas[i] - cost[i];
    int ans = -1;
    for(int i = 0;i < n;i++){
        int s = 0;
        bool check = true;
        for(int j = i;j < n;j++){
            s += diff[j];
            if(s < 0){
                check = false; break;
            }
        }
        if(!check) continue;
        for(int j = 0;j < i;j++){
            s += diff[j];
            if(s < 0){
                check = false; break;
            }
        }
        if(check){
            ans = i; break;
        }

    }

    return ans;
}



int canCompleteCircuit2(vi &gas, vi &cost){
	int current = 0, total = 0, start = 0, n = gas.size();
	rep(i, 0, n){
		int diff = gas[i] - cost[i];
		current += diff, total += diff;
		if(current < 0){
			start = i + 1, current = 0;
		}
	}

	if(total >= 0) return start;
	return -1;
}


//	Bag Of Tokens
int bagOfTokensScore(vi &tokens, int p){
	sort(tokens.begin(), tokens.end());
	int n = tokens.size(), st = 0, en = n - 1, score = 0, maxScore = 0;

	while(st <= en){
		while(st <= en && p >= tokens[st]){
			p -= tokens[st++], score++;
		}
		maxScore = max(maxScore, score);
		if(score != 0 && st <= en){
			p += tokens[en--], score--;
		}
		else return score;
	}

	return maxScore;
}

//	Monotone Increasing Digits
vi monotoneIncreasingDigits(int n){
	int counter = 0, temp = n;
	vi digits;
	while(temp > 0){
		digits.insert(digits.begin(), temp%10);
		counter++, temp /= 10;
	}
	int i = digits.size() - 2, check = digits.size();
	while(i >= 0){
		if(digits[i] > digits[i + 1]){
			digits[i + 1] = 9, digits[i] -= 1, check = i + 1;
		}
		i--;
	}
	i = 0;
	int ret = 0;
	while(i < digits.size() && digits[i] == 0) i++;
	while(i < digits.size()){
		if(i >= check) ret = ret*10 + 9;
		else ret = ret*10 + digits[i];
		i++;
	}
	return ret;
}


int main(){
	int n;
	cin >> n;
	vi ans = monotoneIncreasingDigits(n);
	for(int &a: ans) cout << a;
	cout << "\n";
	return 0;
}






