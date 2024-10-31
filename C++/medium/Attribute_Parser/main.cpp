#include "Attribute_Parser.hpp"

using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N, Q;
    cin >> N >> Q;
    cin.ignore();
    char input[N][200];

    int level = 0;

    std::vector<Tag> root;
    for (int i = 0; i < N; i++)
        std::cin.getline(input[i], 200);
        int i = 0;
    parse(root, i, input, N);

    root[0].children.front().print_tag();
    
    return 0;
}
