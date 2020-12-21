#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>

using namespace std;

class Solution{
public:
	int minimumOneBitOperations(int n){
		string bits = "";
		while(n > 0){
			bits += char((n&1) + '0');
			n = (n>>1);
		}
	}
};

int main(){

	return 0;
}