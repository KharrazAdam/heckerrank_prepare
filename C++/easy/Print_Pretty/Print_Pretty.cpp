#include <iostream>
#include <iomanip> 
using namespace std;

int main() {
	int T; cin >> T;
	cout << setiosflags(ios::uppercase);
	cout << setw(0xf) << internal;
	while(T--) {
		double A; cin >> A;
		double B; cin >> B;
		double C; cin >> C;
        std::cout << std::setfill('_');
        printf("0x%llx\n", (unsigned long long)(A));
        std::cout 
        << std::setfill('_') // The fill character
        << std::right        // right justify
        << std::setw(15)     // field width
        << std::fixed    
        << showpos    // fixed precision
        << std::setprecision(2)
        << B << endl;
        cout.clear();
        std::cout
        << std::scientific
        << std::setprecision(9)
        << noshowpos
        << C 
        << endl;
		/* Enter your code here */
	}
	return 0;

}