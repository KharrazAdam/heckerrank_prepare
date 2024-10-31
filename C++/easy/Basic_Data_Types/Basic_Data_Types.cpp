#include <iostream>
#include <cstdio>
#include <stdio.h>
using namespace std;

int main() {
    // Complete the code.
    int a;
    long b;
    char c;
    float f;
    double d;
    scanf("%d %ld %c %f %lf", &a, &b, &c, &f, &d);
    printf("%d\n%ld\n%c\n%.3f\n%lf\n", a, b, c, f, d);
    
    return 0;
}