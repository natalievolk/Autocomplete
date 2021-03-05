#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "autocomplete.h"


double get_weight(char *line) {
    while(*line == ' ') {
        line++;
    }

    // get weight
    double weight = 0;
    while(isdigit(*line)) {
        weight = weight*10;
        weight = weight + (*line-'0');
        line++;
    }
    // add decimal portion to weight if applicable
    if (*line == '.') {
        line++;
        double mult = 0.1;
        while(isdigit(*line)) {
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
    // cast to struct term
    struct term *a_struct = (struct term *)a;
    struct term *b_struct = (struct term *)b;

    // return string comparison of terms
    return strcmp(a_struct->term, b_struct->term);
}

void read_in_terms(struct term **terms, int *pnterms, char *filename) {
    char line[200];     // assuming terms not longer than 200
    FILE *fp = fopen(filename, "r");

    *pnterms = atol(fgets(line, sizeof(line), fp)); // store number of terms in file

    *terms = (struct term*)malloc(sizeof(struct term)*(*pnterms));

    for(int i = 0; i < *pnterms; i++){
        fgets(line, sizeof(line), fp);  //read in at most sizeof(line) characters
                                        //(including '\0') into line.


        // assign weight and term from file input to memory block
        (*terms)[i].weight = get_weight(line);
        strcpy(((*terms)[i].term), get_term(line));
    }
    fclose(fp);     // close file
    
    qsort(*terms, *pnterms, sizeof(struct term), compare_term);     // quicksort    
}

// binary search to find lowest match
int lowest_match(struct term *terms, int nterms, char *substr) {
    int low = 0;
    int high = nterms-1;
    int len = strlen(substr);
    int i;

    while(high>=low) {
        i = (high+low)/2;   // middle index to start search from

        //int compare = strncmp((terms + i)->term, substr, len);    // equivalent to below line
        int compare = strncmp(terms[i].term, substr, len);  // only comparing length of substr to each term
        if (compare > 0) {
            high = i-1;
        } else if (compare < 0) {
            low = i+1;
        } else if (compare == 0) {
            if (i == 0  ||  strncmp(terms[i-1].term, substr, len) != 0) {
                return i;
            } else {
                high = i-1;
            }
        }
    }
    return -1;      // returns -1 if no matches are found
}

// binary search to find highest match
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
    return -1;      // returns -1 if no matches were found
}

// function to use for weight qsort
int compare_weight(const void *a, const void *b) {    
    struct term *a_struct = (struct term *)a;
    struct term *b_struct = (struct term *)b;
 
    if ((b_struct->weight) - (a_struct->weight) > 0) {
        return 5;       // just needs to return a positive number
    } else if ((b_struct->weight) - (a_struct->weight) < 0) {
        return -3;      // can return any negative number
    } else {
        return 0;       // if weights are same return zero
    }
}

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr) {
    int ans_high = highest_match(terms, nterms, substr);
    int ans_low = lowest_match(terms, nterms, substr);

    if (ans_high == -1) {
        *n_answer = 0;      // if there are no matches, n_answers is set to zero
    } else {
        *n_answer = ans_high - ans_low + 1; // otherwise, set to difference in indices between highest and lowest answer
        
        // add all answers to memory block
        int k = 0;
        *answer = (struct term*)malloc(sizeof(struct term)*(*n_answer));
        for (int i = ans_low; i <= ans_high; i++) {
            (*answer)[k].weight = terms[i].weight;
            strcpy((*answer)[k].term, terms[i].term);
            k++;
        }

        // qsort by decreasing weight
        qsort(*answer, *n_answer, sizeof(struct term), compare_weight);
    }    
}