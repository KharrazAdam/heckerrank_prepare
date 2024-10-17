#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//Complete the following function.


void calculate_the_maximum(int n, int k) {
  //Write your code here.
  int a = 0;
  int o = 0;
  int x = 0;
  
  for (int i = 1; i < n ; i++) {
    for (int j = i + 1; j <= n; j++) {
        int tmp = i & j;
        if (tmp > a && tmp < k)
            a = tmp;
        tmp = i | j;
        if (tmp > o && tmp < k)
            o = tmp;
        tmp = i ^ j;
        if (tmp > x && tmp < k)
            x = tmp;
    }
  } 
    printf("%d\n%d\n%d\n", a, o, x);
}


int main() {
    int n, k;
  
    scanf("%d %d", &n, &k);
    calculate_the_maximum(n, k);
 
    return 0;
}
