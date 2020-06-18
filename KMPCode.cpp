#include <iostream>
#include <vector>

using namespace std;;

// Finding Longest Prefix which is also a suffix for each index of pattern
vector<int> lps(string pattern)
{
	vector<int> ans(pattern.length());
	int i = 0, j = 0;
	ans[i] = 0;
	i++;
	while(i < pattern.length())
	{
		if(pattern[i] == pattern[j]) ans[i] = j+1, i++, j++;
		else if(j == 0) ans[i] = 0, i++;
		else{
			while(j != 0)
			{
				if(pattern[i] == pattern[j]) break;
				j = ans[j-1];
			}
		}
	}
	return ans;
}


bool KMPCode(string pattern, string text)
{
	if(pattern == "") return true;
	vector<int> lp = lps(pattern);
	bool isFound = false;
	int i = 0, j = 0;
	while(i < text.length())
	{
		if(text[i] == pattern[j]) i++, j++;
		else if(j == 0) i++;
		else
		{
			while(j != 0)
			{
				if(pattern[i] == pattern[j]) break;
				j = lp[j-1];
			}
		}

		if j == pattern.length() return true;
	}

	return j == pattern.length()
}

int main()
{
	string text, pattern;
	cin >> text >> pattern;
	cout << KMPCode(pattern, text) << endl;
	return 0;
}

