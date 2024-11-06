#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int Q, type, Y;
    string X;
    std::map <string , int> m;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        cin >> type >> X;
        if (type == 1) {
            cin >> Y;
            m[X] += Y;
        }
        else if (type == 2)
            m.erase(X);
        else if (type == 3)
            cout << m[X] << endl;
    }
    return 0;
}
