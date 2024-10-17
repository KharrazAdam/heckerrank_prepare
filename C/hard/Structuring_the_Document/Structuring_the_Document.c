#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include<stdio.h>
#include<string.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};

typedef struct word word;
typedef struct sentence sentence;
typedef struct paragraph paragraph;
typedef struct document document;

// struct document get_document(char* text) {
//     /**
//      * @brief initialize first paragraph->sentence->word;
//      * @note bach mn daba lfo9 n3emlo ghir realloc alm3elem
//     */
//     document    doc;
//     paragraph   *par = doc.data = calloc(1, sizeof(paragraph));
//     sentence    *sen = doc.data[par->sentence_count].data = calloc(1, sizeof(sentence));
//     word        *wor = doc.data[sen->word_count].data[sen->word_count].data = calloc(1, sizeof(word));
//     wor->data = NULL;

//     int len = strlen(text);
//     int start = 0;
//     doc.paragraph_count = 0;

//     for (int i = 0; i <= len - 1; i++) {
//         if (text[i] == ' ' || text[i] == '.' || text[i] == '\n' || text[i] == '\0') {
//             sen->word_count++;

//             wor->data = strndup(text + start, i - start);
//             sen->data = realloc(sen->data, (sen->word_count + 1) * sizeof(char*));
//             wor = &sen->data[sen->word_count];
//             start = i + 1;
            
//             if (text[i] == '.') {
//                 par->sentence_count++;

//                 par->data = realloc(sen, (par->sentence_count + 1) * sizeof(sentence)); 
//                 sen = &par->data[par->sentence_count];
//                 sen->data = calloc(1, sizeof(word));
//                 wor = &sen->data[sen->word_count];
//                 } else if (text[i] == '\n') {
//                 doc.paragraph_count++;

//                 doc.data = realloc(doc.data, (doc.paragraph_count + 1) * sizeof(paragraph));
//                 par = &doc.data[doc.paragraph_count];
//                 par->data = calloc(1, sizeof(sen));
//                 sen = par->data;
//                 sen->data = calloc(1, sizeof(word));
//             }
//         }
//     }

//     return doc;
// }

struct document get_document(char* text) {
    document doc;
    doc.paragraph_count = 0;
    doc.data = calloc(1, sizeof(paragraph));

    paragraph* par = &doc.data[doc.paragraph_count];
    par->sentence_count = 0;
    par->data = calloc(1, sizeof(sentence));

    sentence* sen = &par->data[par->sentence_count];
    sen->word_count = 0;
    sen->data = calloc(1, sizeof(word));

    word* wor = &sen->data[sen->word_count];
    wor->data = NULL;

    int len = strlen(text);
    int start = 0;

    for (int i = 0; i <= len; i++) {
        if (text[i] == ' ' || text[i] == '.' || text[i] == '\n' || text[i] == '\0') {
            wor->data = strndup(text + start, i - start);
            sen->word_count++;
            sen->data = realloc(sen->data, (sen->word_count + 1) * sizeof(word));
            wor = &sen->data[sen->word_count];
            start = i + 1;

            if (text[i] == '.') {
                par->sentence_count++;
                par->data = realloc(par->data, (par->sentence_count + 1) * sizeof(sentence));

                sen = &par->data[par->sentence_count];
                sen->word_count = 0;
                sen->data = calloc(1, sizeof(word));
                wor = &sen->data[sen->word_count];
            }

            if (text[i] == '\n') {
                doc.paragraph_count++;
                doc.data = realloc(doc.data, (doc.paragraph_count + 1) * sizeof(paragraph));

                par = &doc.data[doc.paragraph_count];
                par->sentence_count = 0;
                par->data = calloc(1, sizeof(sentence));

                sen = &par->data[par->sentence_count];
                sen->word_count = 0;
                sen->data = calloc(1, sizeof(word));
                wor = &sen->data[sen->word_count];
            }
        }
    }

    return doc;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    return Doc.data[n - 1].data[m - 1].data[k - 1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    return Doc.data[m - 1].data[k - 1];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k - 1];
}

void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
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

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}