#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    char ch;
    char s[strlen("Welcome To C!!")] ;

    scanf("%s", &ch);
    printf("%c\n", ch);
    scanf("%s", s);
    printf("%s\n", s);
    for (int i = 0; i < 3; i++) {
        scanf("%s", s);
        printf("%s%c", s, i != 2 ? ' ' : '\n');
    }
    return 0;
}
