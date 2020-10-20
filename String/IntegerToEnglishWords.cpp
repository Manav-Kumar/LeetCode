#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <cmath>
#include <math.h>
#include <unordered_set>
#include <string>
#include <cmath>
using namespace std;

#define ll long long
#define vl vector<ll>
#define vll vector<vl>
#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>
#define vvb vector<vb>

string numberToWords(int num)
{
	if(num == 0) return "Zero";
	string s = to_string(num);
	vector<string> places {" ", "Thousand ", "Million ", "Billion "};
	vector<vector<string> > values(10, vector<string> (3,""));
	for(int i = 1;i <= 9;i++){
		if(i == 1){
			values[i][0] = "One ";
			values[i][2] = "One Hundred ";
		}
		else if(i == 2){
			values[i][0] = "Two ";
			values[i][1] = "Twenty ";
			values[i][2] = "Two Hundred ";
		}
		else if(i == 3){
			values[i][0] = "Three ";
			values[i][1] = "Thirty ";
			values[i][2] = "Three Hundred ";
		}
		else if(i == 4){
			values[i][0] = "Four ";
			values[i][1] = "Forty ";
			values[i][2] = "Four Hundred ";
		}
		else if(i == 5){
			values[i][0] = "Five ";
			values[i][1] = "Fifty ";
			values[i][2] = "Five Hundred ";
		}
		else if(i == 6){
			values[i][0] = "Six ";
			values[i][1] = "Sixty ";
			values[i][2] = "Six Hundred ";
		}
		else if(i == 7){
			values[i][0] = "Seven ";
			values[i][1] = "Seventy ";
			values[i][2] = "Seven Hundred ";
		}
		else if(i == 8){
			values[i][0] = "Eight ";
			values[i][1] = "Eighty ";
			values[i][2] = "Eight Hundred ";
		}
		else if(i == 9){
			values[i][0] = "Nine ";
			values[i][1] = "Ninety ";
			values[i][2] = "Nine Hundred ";
		}
	}

	map<string,string> ones;
	ones["10"] = "Ten ", ones["11"] = "Eleven ", ones["12"] = "Twelve ", ones["13"] = "Thirteen ",
	ones["14"] = "Fourteen ", ones["15"] = "Fifteen ", ones["16"] = "Sixteen ", ones["17"] = "Seventeen ",
	ones["18"] = "Eighteen ", ones["19"] = "Nineteen ";


	vector<string> finalAns;
	int count = 0, i = s.size() - 3;
	for(;i >= 0;){
		
		string piece = s.substr(i, 3);
		string ans = values[piece[0] - '0'][2];

		if(piece[1] == '1') ans += ones[piece.substr(1)];
		else ans += values[piece[1] - '0'][1] + values[piece[2] - '0'][0];

		if(ans != ""){
			ans += places[count];
		}

		count++;
		finalAns.push_back(ans);
		i -= 3;
	}

	if(i < 0 && i > -3){
		i += 2;
		string piece = s.substr(0, i + 1);
		string ans = "";
		if(piece.size() == 1){
			ans = values[piece[0] - '0'][0];
		}
		else if(piece.size() == 2){

			if(piece[0] == '1') ans = ones[piece];
			else ans = values[piece[0] - '0'][1] + values[piece[1] - '0'][0];
		}

		if(ans != ""){
			ans += places[count];
		}

		finalAns.push_back(ans);
	}
	string ans = "";
	for(int i = finalAns.size()-1;i >= 0;i--){
		ans += finalAns[i];
	}
	int sz = ans.size();
	while(ans[sz - 1] == ' ') sz--;
	return ans.substr(0, sz);
}

string numberToWords2(int num)
{
	if(num == 0) return "Zero";

	string arr[20] = {"", "One ", "Two ", "Three ", "Four ", "Five ", "Six ", "Seven ", "Eight ", "Nine ",
		"Ten ", "Eleven ", "Twelve ", "Thirteen ", "Fourteen ", "Fifteen ", "Sixteen ", "Seventeen ",
		"Eighteen ", "Nineteen "};
	string secondsarr[] = { "", "Ten ", "Twenty ", "Thirty ", "Forty ", "Fifty ", "Sixty ", "Seventy ",
		"Eighty ", "Ninety " };

	string places[4] =  {" ", "Thousand ", "Million ", "Billion "};
	int count = 0;
	string finalAns = "";
	while(num >= 100){
		int curr = num%1000;
		int p2, p1, p0;
		p2 = curr/100, curr %= 100;
		p1 = curr/10, curr %= 10;
		p0 = curr;
		string ans = "";
		if(p2) ans = arr[p2] + "Hundred ";

		if(p1 == 1) ans += arr[p1*10 + p0];
		else{
			ans += secondsarr[p1] + arr[p0];
		}
		if(ans != "") ans += places[count];
		
		finalAns = ans + finalAns;
		count++;
		num /= 1000;
	}

	if(num){
		string ans = "";
		if(num <= 19) ans = arr[num];
		else{
			int p1, p0;
			p1 = num/10, num %= 10;
			p0 = num;
			cout << p1 << " " << p0 << "\n";
			ans = secondsarr[p1] + arr[p0];
		}
		if(ans != "") ans += places[count];

		finalAns = ans + finalAns;

	}

	int sz = finalAns.size();
	while(finalAns[sz - 1] == ' ') sz--;
	return finalAns.substr(0, sz);
}



int main(){
	int num;
	cin >> num;
	cout << numberToWords2(num) << "\n";
	return 0;
}