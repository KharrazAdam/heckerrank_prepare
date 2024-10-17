#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char **av) 
{

    int n;
    scanf("%d", &n);
    int lines = n * 2 - 1;

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < lines; j++) {

            int a = abs(n - i - 1);
            int b = abs(n - j - 1);
            int c = a > b ? a : b ;
            printf("%d", c);
            j == lines - 1 ? printf("\n") : printf(" ");
        }
    }
    return 0;
}
