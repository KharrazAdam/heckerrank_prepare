#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int N, x;
    cin >> N;
    vector<int> arr;

    for (int i = 0; i < N; i++) {
        cin >> x;
        arr.push_back(x);
    }
    cin >> x;
    arr.erase(arr.begin() + x - 1);
    
    cin >> x >> N;

    arr.erase(arr.begin() + x - 1, arr.begin() + N - 1);
    int si = arr.size();
    
    cout << si << endl;

    for (int i = 0; i < si; i++) {
        cout << arr[i];
        i != si - 1 ? cout << " " : cout << endl;
    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    return 0;
}
