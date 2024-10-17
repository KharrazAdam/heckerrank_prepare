#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>



int main() 
{
    int a, b;
    scanf("%d\n%d", &a, &b);
  	// Complete the code.
        char *numbers[] = {
        "zero",
        "one", 
        "two", 
        "three", 
        "four", 
        "five", 
        "six", 
        "seven", 
        "eight", 
        "nine"
    };
    
    for (; a <= b && a < 10; a++)
        printf("%s\n", numbers[a]);
    for (; a <= b; a++)
        a % 2 ? printf("odd\n") : printf("even\n");
    return 0;
}

Sum_of_Digits_of_a_Five_Digit_Number