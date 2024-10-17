#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


int main()
{
    int in[2];
    double db[2];

    scanf("%d %d", &in[0], &in[1]);
    scanf("%lf %lf", &db[0], &db[1]);

    printf("%d %d\n%.1f %.1f\n", in[0] + in[1], in[0] - in[1], db[0] + db[1], db[0] - db[1]);
    return 0;
}