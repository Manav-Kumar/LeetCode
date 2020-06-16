#include <iostream>
#include <set>
#include <vector>
using namespace std;

class RangeModule3
{
public:
	set<pair<int, int>> s;
    RangeModule3() {
        
    }
    
    void addRange(int left, int right) {
        auto it = s.upper_bound({left, right});
        if (it != s.begin() && left > (--it)->second)
            ++it;
        while (it != s.end() && it->first <= right) {
            left = min(left, it->first);
            right = max(right, it->second);
            it = s.erase(it);
        }
        s.insert({left, right});
    }
    
     bool queryRange(int left, int right) {
        auto it = s.upper_bound({left, INT_MAX});
        return it != s.begin() && right <= prev(it)->second;
    }
    
    void removeRange(int left, int right) {
        auto it = s.upper_bound({left, right});
        if (it != s.begin() && left >= (--it)-> second)
            ++it;
        while (it != s.end() && right > it->first) {
            if (left > it->first)
                s.insert({it->first, left});
            if (right < it->second)
                s.insert({right, it->second});
            it = s.erase(it);
        }
    }
};


int main()
{
	RangeModule3 r;
	r.addRange(10,20);
	r.removeRange(14,16);
	cout << r.queryRange(10,14) << " " << r.queryRange(13,15) << " " << r.queryRange(16,17) << endl;
	set<int> s;
	auto it2 = s.upper_bound(2);
	if(it2 == s.end()) cout << "pk";
 	return 0;
}

