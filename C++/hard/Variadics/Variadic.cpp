#include <iostream>
using namespace std;

// Enter your code for reversed_binary_value<bool...>()
#include <iostream>

// Empty base case for print_single (recursive function)
void print_single() {}

template <bool First>
int reversed_binary_value() {
    return First ? 1 : 0;
}

template <bool First, bool Next, bool... Rest>
int reversed_binary_value() {
    int current_value = First ? 1 : 0;
    return current_value + (reversed_binary_value<Next, Rest...>() << 1); // Recursive call
};

template <int n, bool...digits>
struct CheckValues {
  	static void check(int x, int y)
  	{
    	CheckValues<n-1, 0, digits...>::check(x, y);
    	CheckValues<n-1, 1, digits...>::check(x, y);
  	}
};

template <bool...digits>
struct CheckValues<0, digits...> {
  	static void check(int x, int y)
  	{
    	int z = reversed_binary_value<digits...>();
    	std::cout << (z+64*y==x);
  	}
};

int main()
{
  	int t; std::cin >> t;

  	for (int i=0; i!=t; ++i) {
		int x, y;
    	cin >> x >> y;
    	CheckValues<6>::check(x, y);
    	cout << "\n";
  	}
}
