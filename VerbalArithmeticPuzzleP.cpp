#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <unordered_set>

using namespace std;

class Solve
{
public:
	Solve(vector<string> words,string result,bool &initailCheck): Words(words), c2i(vector<int>(26,-1)),
				used(vector<bool>(10,false))
	{
		Words.push_back(result);
		for(string &w: Words)
		{
			if(w.size() > result.size() && w != result) initailCheck = false;
			reverse(w.begin(), w.end());
		}
	}
	bool solve(int wordIdx,int listIdx,int sum)
	{
		//
		if(wordIdx == Words.back().size()) return sum == 0;

		if(listIdx == Words.size())
		{
			if(sum%10 == 0) return solve(wordIdx+1, 0, sum/10);
			else return false;
		}

		if(wordIdx >= Words[listIdx].size()) return solve(wordIdx, listIdx+1,sum);
		
		if(c2i[Words[listIdx][wordIdx] - 'A'] != -1)
		{
			int val = c2i[Words[listIdx][wordIdx] - 'A'];
			if(val == 0 && wordIdx == Words[listIdx].size()-1) return false;
			return solve(wordIdx, listIdx+1, sum + ((listIdx == Words.size()-1)?-val:val));
		}
		else
		{
			for(int k = (wordIdx == Words[listIdx].size()-1)?1:0;k<10;++k)
			{
				if(!used[k])
				{
					used[k] = true;
					c2i[Words[listIdx][wordIdx] - 'A'] = k;
					int val = (listIdx == Words.size()-1)?-k:k;
					if(solve(wordIdx, listIdx+1,sum + val)) return true;

					used[k] = false;
					c2i[Words[listIdx][wordIdx] - 'A'] = -1;					
				}
			}
		}

		return false;
	}

private:
	vector<string> Words;
	vector<int> c2i;
	vector<bool> used;
};

bool isSolvable(vector<string>& words,string result)
{
	bool initailCheck = true;
	Solve sv(words, result, initailCheck);
	if(!initailCheck) return false;
	return sv.solve(0,0,0);
}

int main()
{
	vector<string> words;
	string result;
	int n;
	cin >> n;
	words.resize(n);
	for(string &s: words) cin >> s;
	cin >> result;
	cout << isSolvable(words, result) << endl;
	return 0;
}

