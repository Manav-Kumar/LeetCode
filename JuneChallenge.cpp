#include <iostream>
#include <vector>
using namespace std;

#define rep(i,a,b) for(int i = a;i < b;i++)

// Reconstruct a queue
vector<vector<int> > reconstructQueue(vector<vector<int> >& people)
{
	vector<vector<int> > copy = people;
	vector<vector<int> > ans;
	int prevHt = -1, index = -1;
	rep(i,0,copy.size())
	{
		int currHt = INT_MAX, index = -1;
		rep(j,0,copy.size())
		{
			if(prevHt >= copy[j][0]) copy[j][1]--;
			if(copy[j][1] == 0 && copy[j][0] < currHt) currHt = copy[j][0], index = j;
		}
		ans.push_back(people[index]);
		prevHt = copy[index][0];
	}
	return ans;
}

// Coin Change2
int change(int amount, vector<int>& coins,int **dp,int index)
{
	if(amount == 0) return 1;
	if(index < 0) return 0;
	if(dp[index][amount] != -1) return dp[index][amount];
	int total = 0;
	for(int i = 0;amount >= (i*coins[index]);i++)
	{
		total += change(amount - i*coins[index], coins,dp, index-1);
	}
	dp[index][amount] = total;
	return total;
}

//Memoization
int change2(int amount,vector<int>& coins)
{
	if(amount == 0) return 1;
	if(coins.size() == 0) return 0;
	int **dp = new int*[coins.size()];
	rep(i,0, coins.size()) dp[i] = new int[amount+1]();

	// Filling 1st Row
	rep(at,0,amount+1)
	{
		if(at >= coins[0] && at%coins[0] == 0) dp[0][at] = 1;
		else dp[0][at] = 0;
	}
	dp[0][0] = 1;
	rep(index, 1, coins.size())
	{
		rep(at,0,amount+1)
		{
			dp[index][at] = 0;
			for(int i = 0;at >= (i*coins[index]);i++)
			{
				dp[index][at] += dp[index-1][at - i*coins[index]];
			}
		}
	}
	int ans = dp[coins.size()-1][amount];
	rep(i,0,coins.size()) delete []dp[i];
	delete []dp;
	return ans;
}


// Validate IP Address
string validIPAddress(string IP) {
    string ans = "@";
    for(int i = 0;i < IP.size();i++)
    {
        if(ans == "@")
        {
            if(IP[i] == ':') ans = "v6";
            else if(IP[i] == '.') ans = "v4";
        }
        else if(ans == "v6" && IP[i] == '.') return "Neither";
        else if(ans == "v4" && IP[i] == ':') return "Neither";
    }
    
    if(ans == "v6")
    {
        int ct = 0, outerCount = 0;
        for(int i = 0;i < IP.size();i++)
        {
            if(IP[i] == ':') 
            {
                if(ct == 0 || outerCount > 6) return "Neither";
                ct = 0,outerCount++;
                continue;
            }
            if(IP[i] >= 'a' && IP[i] <= 'f') IP[i] = (IP[i] - 'a') + 'A';
            if(ct >= 4 ) return "Neither";
            if((IP[i] >= '0' && IP[i] <= '9') || (IP[i] >= 'A' && IP[i] <= 'F')) {}
            else return "Neither";
            ct++;
        }
        if(ct == 0 || outerCount != 7) return "Neither";
        return "IPv6";
    }
    
    if(ans == "v4")
    {
        int curr = 0,ct = 0,outerCount = 0;
        for(int i = 0;i < IP.size();i++)
        {
            if(IP[i] == '.')
            {
                if(ct == 0 || curr > 255 || outerCount > 2) return "Neither";
                ct = 0, curr = 0, outerCount++;
                continue;
            }
            if((ct >= 1 && curr == 0) || curr > 255 || IP[i] > '9' || IP[i] < '0') return "Neither";
            curr = curr*10 + int(IP[i] - '0');
            ct++;
        }
        if(ct == 0 || curr > 255 || outerCount != 3) return "Neither";
        return "IPv4";
    }
    return "Neither";
}



int main()
{
	int amount,size;
	vector<int> coins;
	cin >> amount >> size;
	coins.resize(size);
	for(int &c: coins) cin >> c;
	int **dp = new int*[size];
	rep(i,0,size) dp[i] = new int[amount+1], fill(dp[i], dp[i] + amount + 1, -1);
	cout << change(amount, coins, dp, size-1) << endl;
	cout << change2(amount, coins) << endl;
	return 0;
}




