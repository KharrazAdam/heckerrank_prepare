#include <iostream>
#include <string>
using namespace std;

int main() {
	// Complete the program
    string str[2];
    cin >> str[0] >> str[1];
    cout << str[0].size() << " " << str[1].size() << endl << str[0] + str[1] << endl;
    swap(str[1][0],str[0][0]);
    cout << str[0] << " " << str[1] << endl;
    return 0;
}