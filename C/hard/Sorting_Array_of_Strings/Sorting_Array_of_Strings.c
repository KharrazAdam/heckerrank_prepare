#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lexicographic_sort(const char* a, const char* b) {
    return strcmp(a, b) >= 0 ? 1: 0;
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    return strcmp(a, b) >= 0 ? 0: 1;
}

int dis(const char *str) {
    char alp[26] = {0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0};
    int ret = 0;
    
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if (alp[str[i] -'a'] == 0)
        {
            alp[str[i] -'a'] = '*';
            ret++;
        }
    }
    return ret;
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    return !(dis(a) - dis(b)) ? lexicographic_sort(a, b) : dis(a) > dis(b);
}

int sort_by_length(const char* a, const char* b) {
    const int len_a = strlen(a);
    const int len_b = strlen(b);
    
    if (len_a == len_b)
        return lexicographic_sort(a, b);
    return len_a > len_b  ? 1: 0;
}

void swap(char **a, char **b) {
    char *tmp = *a;
    *a = *b;
    *b = tmp;
        
}

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)){
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len -1; j++) {
            if (cmp_func(arr[j], arr[j + 1]) > 0)
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}