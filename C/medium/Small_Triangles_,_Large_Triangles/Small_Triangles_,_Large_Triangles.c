#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;

void    swap(triangle *a, triangle *b) {
    triangle tmp;
    
    tmp = *a;
    *a = *b;
    *b = tmp;
};

void    swapDbl(double *a, double *b) {
    double tmp;
    
    tmp = *a;
    *a = *b;
    *b = tmp;

}
double    P(triangle tr) {
    return (tr.a + tr.b + tr.c) / 2.0;
}

double area(triangle tr, double P) {
    return sqrt(P * (P - tr.a) * (P - tr.b) * (P - tr.c));
} 

void sort_by_area(triangle* tr, int n) {
    /**
    * Sort an array a of the length n
    */
    double *arr = calloc(n, sizeof(double));

    for (int i = 0; i < n; i++) {
        arr[i] = area(tr[i], P(tr[i]));
    }
    
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&tr[j], &tr[j + 1]);
                swapDbl(&arr[j], &arr[j + 1]);
            }
        }
    free(arr);
}

int main()
{
	int n;
	scanf("%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}