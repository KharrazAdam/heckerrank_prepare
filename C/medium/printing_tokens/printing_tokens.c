#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
int main() {

    char *s;
    s = malloc(1024 * sizeof(char));
    scanf("%[^\n]", s);
    s = realloc(s, strlen(s) + 1);
    //Write your logic to print the tokens of the sentence here.

    const size_t size = strlen(s);
    for (size_t i = 0; i < size; i++) {
        const char c = s[i] != ' ' ? s[i]: '\n';
        write(1, &c, 1);
    }
    return 0;
}