#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    char *num = calloc(1000, sizeof(char));
    char *tmp = num;
    scanf("%s", num);
    int *ten = calloc(10, sizeof(int));
    for (; *num != 0 ; num++) {
        if (*num  >= '0' && *num <= '9')
            ten[*num - '0']++;
    }
    
    for (size_t i = 0; i < 10; i++)
    {
        printf("%d ", ten[i]);
    }
    
    free(ten);
    free(tmp);
    return 0;
}
