#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <map>
using namespace std;


int main() {
    int N, S, P, Q;
    cin >> N >> S >> P >> Q;
    unsigned int *a = (unsigned int *)calloc(N, sizeof(unsigned int));
    unsigned int pow_32 =  pow(2, 31);
    uint32_t maxUint32 = std::numeric_limits<uint32_t>::max();
    char *c = (char *)calloc(maxUint32 / 32, sizeof(char));
    a[0] = S % (unsigned int)pow_32;

    c[a[0] / 32] |= (1 << (a[0] % 8)); 
    int tmp = N;

    for (int i = 1; i <= N; i++) {
        a[i] = a[i - 1] * P + Q;

        if (a[i] < maxUint32) { 
            if (c[a[i] / 32] & (1 << (a[i] % 8))) {
                tmp--; 
            } else {
                c[a[i] / 32] |= (1 << (a[i] % 8));
            }
        } else tmp--;
    }

    cout << tmp << endl;
    free (a);
    free(c);
    return 0;
}