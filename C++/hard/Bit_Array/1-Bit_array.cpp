
#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
using namespace std;

#define MAX_INT  2147483648
#define POW_32 (unsigned int)pow(2, 31)

int main()
{

	std::vector<bool> v;
	v.resize(MAX_INT);	int N, S, P, Q;

	cin >> N >> S >> P >> Q;
    int tmp = N;
    
    unsigned long long pr = S % POW_32;
    v[pr] = true;
    
    for (int i = 1; i < N; i++)    {
        unsigned int af = (pr * P + Q )% POW_32;
        if (v[af] == 1) tmp--;
        else v[af] = true;
        pr = af;
    }
	cout << tmp << endl;
}

