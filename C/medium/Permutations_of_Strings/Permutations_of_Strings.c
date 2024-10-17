#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void    swap(char **a, char **b) {
    char    *tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}


/**
 * @see https://en.wikipedia.org/wiki/Permutation#Generation_in_lexicographic_order 
*/
// int    next_permutation(int n, char **s)
// {
//     /**
//     * Complete this method
//     * Return 0 when there is no next permutation and 1 otherwise
//     * Modify array s to its next permutation
//     */

int    next_permutation(int n, char **s)
{
    int k = -1;

    // Step 1: Find the largest index k such that s[k] < s[k + 1]
    for (size_t i = 0; i < n - 1; i++)
    {
        if (strcmp(s[i], s[i + 1]) < 0)
            k = i;
    }
    
    // If no such k exists, the permutation is the last permutation
    if (k < 0)
        return 0;
    
    // Step 2: Find the largest index l greater than k such that s[k] < s[l]
    
    int l = -1;
    for (size_t i = k + 1; i < n; i++)
    {
        if (strcmp(s[k], s[i]) < 0)
            l = i;
    }

    // Step 3: Swap s[k] with s[l]
    swap(&s[k], &s[l]);
    // Step 4: Reverse the sequence from s[k + 1] to the end
    for (size_t i = k + 1, j = n - 1; i < j; i++, j--)
    {
        swap(&s[j], &s[i]);
    }
    
    return 1; // There is a next permutation
}


int main()
{
	char **s;
	int n;
	scanf("%d", &n);
	s = calloc(n, sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		s[i] = calloc(11, sizeof(char));
		scanf("%s", s[i]);
	}
	do
	{
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));
	for (int i = 0; i < n; i++)
		free(s[i]);
	free(s);
	return 0;
}
int main()
{
	char **s;
	int n;
	scanf("%d", &n);
	s = calloc(n, sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		s[i] = calloc(11, sizeof(char));
		scanf("%s", s[i]);
	}

	do
	{
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));
	for (int i = 0; i < n; i++)
		free(s[i]);
	free(s);
	return 0;
}
