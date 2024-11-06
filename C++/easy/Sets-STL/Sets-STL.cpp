#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    set<int>s;
    int Q, x, y;
    cin >> Q;
    for  (int i = 0; i < Q; i++) {
        cin >> y >> x;
        if (y == 1)
            s.insert(x);
        else if (y == 2)
            s.erase(x);
        else if (y == 3)
            s.find(x) == s.end() ? cout << "No\n" : cout << "Yes\n";
    }
    return 0;
}
