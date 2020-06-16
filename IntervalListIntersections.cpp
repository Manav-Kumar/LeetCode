#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


#define vvi vector<vector<int> > 
#define vi vector<int>


vvi intervalIntersection(vvi& A, vvi& B) {

    int i = 0, j = 0;
    vvi res;
    while(i < A.size() && j < B.size())
    {
        int m = max(A[i][0], B[j][0]);
        int M = min(A[i][1], B[j][1]);
        
        if(m <= M)
        {
            res.push_back(vector<int> {m,M});
            int k = (M == A[i][1]?++i: ++j);
        }
        else if(A[i][1] < B[j][0]) i++;
        else if(A[i][0] > B[j][1]) j++;
    }
    
    return res;
}

int main()
{

}