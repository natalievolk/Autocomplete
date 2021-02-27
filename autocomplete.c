#include <stdlib.h>
#include <stdio.h>
#include "autocomplete.h"

void read_in_terms(struct term **terms, int *pnterms, char *filename) {
    char line[200];
    FILE *fp = fopen(filename, "r");
    for(int i = 0; i < 10; i++){
        fgets(line, sizeof(line), fp);  //read in at most sizeof(line) characters
                                        //(including '\0') into line.
    }
    
    printf("%d\n", 100);
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