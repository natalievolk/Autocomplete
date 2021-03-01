#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "autocomplete.h"


int get_weight(char *line) {
    while(*line == ' ') {
        line++;
    }

    // get weight
    int weight = 0;
    while(isdigit(*line)) {
        weight = weight*10;
        weight = weight + (*line-'0');
        line++;
    }
    if (*line == '.') {
        line++;
        double mult = 0.1;
        while(isdigit(*line)) {
            //weight = weight*10;
            weight = weight + ((*line-'0') * mult);
            line++;
            mult = mult*0.1;
        }
    }
    return weight;
}

// this function could definitely be optimized lol
//  (maybe by combining with get_weight? or just leave it)
char *get_term(char *line) {
    // moves through initial whitespace
    while(isspace(*line)) {
        line++;
    }
    // moves through weight number
    while(isdigit(*line) || (*line == '.')) {
        line++;
    }
    // moves through whitespace between weight and term
    while(isspace(*line)) {
        line++;
    }
    
    char *term = line;
    // removes newline character from end
    while(*line != '\0') {
        if (*line == '\n') {
            *line = '\0';
        }
        line++;
    }
    // returns the term
    return term;
}

int compare_term(const void *a, const void *b) {    
    
    struct term *a_struct = (struct term *)a;
    struct term *b_struct = (struct term *)b;

    //printf("a_struct %s\n", a_struct->term);
    //printf("b_struct %s\n", b_struct->term);

    return strcmp(a_struct->term, b_struct->term);
}

void read_in_terms(struct term **terms, int *pnterms, char *filename) {
    char line[200];     // assuming terms not longer than 200
    FILE *fp = fopen(filename, "r");

    *pnterms = atol(fgets(line, sizeof(line), fp)); // store number of terms
    //printf("%d\n", *pnterms);

    *terms = (struct term*)malloc(sizeof(struct term)*(*pnterms));

    for(int i = 0; i < *pnterms; i++){
        fgets(line, sizeof(line), fp);  //read in at most sizeof(line) characters
                                        //(including '\0') into line.

        //strcpy(((*terms + i)->term), get_term(line));
        //(*terms + i)->weight = get_weight(line);
        (*terms)[i].weight = get_weight(line);
        strcpy(((*terms)[i].term), get_term(line));
    }
    fclose(fp);
    
    qsort(*terms, *pnterms, sizeof(struct term), compare_term);
    for(int i=0; i<*pnterms; i++) {
        //printf("%d %f %s\n", i, (*terms)[i].weight, (*terms)[i].term);;
    }
    
}

int lowest_match(struct term *terms, int nterms, char *substr) {
    int low = 0;
    int high = nterms-1;
    int len = strlen(substr);
    int i;

    while(high>=low) {
        i = (high+low)/2;

        //int compare = strncmp((terms + i)->term, substr, len);
        int compare = strncmp(terms[i].term, substr, len);
        if (compare > 0) {
            high = i-1;
        }
        else if (compare < 0) {
            low = i+1;
        }
        else if (compare == 0) {
            if (i == 0  ||  strncmp(terms[i-1].term, substr, len) != 0) {
                return i;
            }
            else {
                high = i-1;
            }
        }
    }
    return -1;
}

int highest_match(struct term *terms, int nterms, char *substr) {
    int low = 0;
    int high = nterms-1;
    int len = strlen(substr);
    int i;

    while(high>=low) {
        i = (high+low)/2;

        //int compare = strncmp((terms + i)->term, substr, len);
        int compare = strncmp(terms[i].term, substr, len);
        if (compare > 0) {
            high = i-1;
        }
        else if (compare < 0) {
            low = i+1;
        }
        else if (compare == 0) {
            if (i == nterms-1  ||  strncmp(terms[i+1].term, substr, len) != 0) {
                return i;
            }
            else {
                low = i+1;
            }
        }
    }
    return -1;
}

int compare_weight(const void *a, const void *b) {    
    
    struct term *a_struct = (struct term *)a;
    struct term *b_struct = (struct term *)b;

    return (b_struct->weight) - (a_struct->weight);
}

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr) {
    int ans_high = highest_match(terms, nterms, substr);
    int ans_low = lowest_match(terms, nterms, substr);

    if (ans_high == -1) {
        *n_answer = 0;
    } else {
        *n_answer = ans_high - ans_low + 1;
        *answer = (struct term*)malloc(sizeof(struct term)*(*n_answer));

        int k = 0;
        for (int i = ans_low; i <= ans_high; i++) {
            (*answer)[k].weight = terms[i].weight;
            strcpy((*answer)[k].term, terms[i].term);
            k++;
        }

        qsort(*answer, *n_answer, sizeof(struct term), compare_weight);

        for (int i = 0; i < *n_answer; i++) {
            //printf("%d %f %s\n", i, (*answer)[i].weight, (*answer)[i].term);
        }
    }    
}