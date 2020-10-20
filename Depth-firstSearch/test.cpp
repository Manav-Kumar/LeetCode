#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
int main () {
   set<int> set1 = {5,6,7,8,9,10};
   set<int> set2 = {1,2,3,4,6,7};
   set<int> c;
   vector<int> v(10);
   auto st = set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), v.begin());
   // v.resize(st - v.begin());
   // cout<<"The union between the sets has "<< (v.size())<< " elements: "<<endl;
   // for (st = v.begin(); st != v.end(); ++st)
   //    cout<< *st<<" ";
   // cout <<endl;
   return 0;
}