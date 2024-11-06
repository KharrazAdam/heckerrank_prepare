#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    int n, q;
    cin >> n >> q;
    vector<int> a[n];
    
    int k;
    for (int i = 0; i < n; i++) {
        cin >> k;
        a[i].resize(k);
        for (int j = 0; j < k; j++)
            cin >> a[i][j];
    }
    for (int i = 0; i < q; i++)
    {
        cin >> k >> n;
        cout << a[k][n] << endl;
    }
    return 0;
}
