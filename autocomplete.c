#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "autocomplete.h"

// look at piazza @240... i should be able to do terms[i]!!

int get_weight(char *line) {
    while(*line == ' ') {
        line++;
        //printf("%s", "hi");
    }

    // get weight
    int weight = 0;
    while(isdigit(*line)) {
        weight = weight*10;
        weight = weight + (*line-'0');
        line++;
    }
    return weight;
}

char *get_term(char *line) {
    // moves through initial whitespace
    while(isspace(*line)) {
        line++;
    }
    // moves through weight number
    while(isdigit(*line)) {
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

int compare(const void *a, const void *b) {    
    /*
    struct term *a_struct = (struct term *)a;
    struct term *b_struct = (struct term *)b;

    printf("a_struct %s\n", a_struct->term);
    printf("b_struct %s\n", b_struct->term);

    return strcmp(a_struct->term, b_struct->term);
    */
    
    return 4;

    //return 0;

    //strcmp((*terms)->term, ((*terms + sizeof(struct term)*1)->term))
}

void read_in_terms(struct term **terms, int *pnterms, char *filename) {
    char line[200];     // assuming terms not longer than 200
    FILE *fp = fopen(filename, "r");

    *pnterms = atol(fgets(line, sizeof(line), fp)); // store number of terms
    printf("%d\n", *pnterms);

    *terms = (struct term*)malloc(sizeof(struct term)*(*pnterms));

    for(int i = 0; i < *pnterms; i++){
        fgets(line, sizeof(line), fp);  //read in at most sizeof(line) characters
                                        //(including '\0') into line.
        
        // this appears to successfully set term and weight :))
        strcpy(((*terms + sizeof(struct term)*i)->term), get_term(line));
        (*terms + sizeof(struct term)*i)->weight = get_weight(line);

        printf("%f %s\n", (*terms + sizeof(struct term)*i)->weight, ((*terms + sizeof(struct term)*i)->term));
    }
    //qsort(*terms, 3, sizeof(struct term), compare);
}

int lowest_match(struct term *terms, int nterms, char *substr) {
    int low = 0;
    int high = nterms-1;
    int len = strlen(substr);
    int i;

    while(high>=low) {
        i = (high+low)/2;

        int compare = strncmp((terms + sizeof(struct term)*i)->term, substr, len);
        if (compare > 0) {
            high = i-1;
        }
        else if (compare < 0) {
            low = i+1;
        }
        else if (compare == 0) {
            if (i == 0  ||  strncmp((terms + sizeof(struct term)*(i-1))->term, substr, len) != 0) {
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

        int compare = strncmp((terms + sizeof(struct term)*i)->term, substr, len);
        if (compare > 0) {
            high = i-1;
        }
        else if (compare < 0) {
            low = i+1;
        }
        else if (compare == 0) {
            if (i == nterms-1  ||  strncmp((terms + sizeof(struct term)*(i+1))->term, substr, len) != 0) {
                return i;
            }
            else {
                low = i+1;
            }
        }
    }
    return -1;
}
void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr) {
    int a = 0;
}