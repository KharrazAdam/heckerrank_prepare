#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    return document[n - 1][m - 1][k - 1];
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
    return document[m - 1][k - 1];
}

char*** kth_paragraph(char**** document, int k) {
    return document[k - 1];
}

char**** get_document(char* text) {
    
    int len = strlen(text);
    char**** doc = calloc(1, sizeof(char***)); 
    int p = 0, s = 0, w = 0, start = 0;

    doc[p] = calloc(1, sizeof(char**));
    doc[p][s] = calloc(1, sizeof(char*));
    doc[p][s][w] = NULL;

    for (int i = 0; i <= len; i++) {
        if (text[i] == ' ' || text[i] == '.' || text[i] == '\n' || text[i] == '\0') {
            doc[p][s][w] = strndup(text + start, i - start);
            w++;
            doc[p][s] = realloc(doc[p][s], (w + 1) * sizeof(char*));
            doc[p][s][w] = NULL;
            
            start = i + 1;

            if (text[i] == '.') {
                w = 0;
                s++;
                doc[p] = realloc(doc[p], (s + 1) * sizeof(char**));
                doc[p][s] = calloc(1, sizeof(char*));
            } else if (text[i] == '\n') {
                w = 0;
                s = 0;
                p++;
                doc = realloc(doc, (p + 1) * sizeof(char***));
                doc[p] = calloc(1, sizeof(char**));
                doc[p][s] = calloc(1, sizeof(char*));
            }
        }
    }
    return doc;
}

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;

    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}