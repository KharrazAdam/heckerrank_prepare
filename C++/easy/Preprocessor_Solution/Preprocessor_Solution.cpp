#include <iostream>
#define toStr(x) #x
#define io(v) cin >> v
#define foreach(v, i)\
    int size = v.size();\
    for (int i = 0; i < size; i++)

#define INF 10000000
#define FUNCTION(name, operator) \
    void name(int &tmp, int candidate) { tmp = (candidate operator tmp) ? candidate : tmp; }

#include <iostream>
#include <vector>
using namespace std;

FUNCTION(minimum, <)
FUNCTION(maximum, >)

int main(){
	int n; cin >> n;
	vector<int> v(n);
	foreach(v, i) {
		io(v)[i];
	}
	int mn = INF;
	int mx = -INF;
	foreach(v, i) {
		minimum(mn, v[i]);
		maximum(mx, v[i]);
	}
	int ans = mx - mn;
	cout << toStr(Result =) <<' '<< ans;
	return 0;

}