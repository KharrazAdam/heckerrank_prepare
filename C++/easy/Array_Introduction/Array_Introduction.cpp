#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int n;
    cin >> n;
    int arr[n];

    for (size_t i = 0; i < n; i++)
        cin >> arr[i];

    for (n -= 1; n >= 0; n--) {
        cout << arr[n];
        n == 0 ? cout << endl : cout << " ";
    }

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
