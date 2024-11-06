#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N;
    cin >> N;
    vector<int > v(N);
    for (int i = 0; i < N; i++)
        cin >> v[i];
    int Q;
    cin >> Q;
    int Y;
    for (int i = 0; i < Q; i++) {
        cin >> Y;
        if (binary_search(v.begin(), v.end(), Y))
            cout << "Yes ";
        else cout << "No ";
        cout << lower_bound(v.begin(), v.end(), Y) - v.begin() + 1 << endl;
    }
    return 0;
}
