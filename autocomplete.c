#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "autocomplete.h"

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

void read_in_terms(struct term **terms, int *pnterms, char *filename) {
    char line[200];     // assuming terms not longer than 200
    FILE *fp = fopen(filename, "r");

    *pnterms = atol(fgets(line, sizeof(line), fp)); // store number of terms
    printf("%d\n", *pnterms);

    *terms = (struct term*)malloc(sizeof(struct term)*(*pnterms));

    for(int i = 0; i < 2; i++){
        fgets(line, sizeof(line), fp);  //read in at most sizeof(line) characters
                                        //(including '\0') into line.
        
        /*
        int weight = get_weight(line);
        char *term = get_term(line);
        printf("%d %s\n", weight, term);
        */


        // this appears to successfully set term and weight :))
        strcpy(((*terms + sizeof(struct term)*i)->term), get_term(line));
        (*terms + sizeof(struct term)*i)->weight = get_weight(line);

        printf("%f\n", (*terms + sizeof(struct term)*i)->weight);
        printf("%s\n", ((*terms + sizeof(struct term)*i)->term));
    }
}

int lowest_match(struct term *terms, int nterms, char *substr) {
    return 0;
}
int highest_match(struct term *terms, int nterms, char *substr) {
    return 0;
}
void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr) {
    int a = 0;
}