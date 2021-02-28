#include "autocomplete.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "test2_cities.txt");
    
    printf("lowest match %d\n", lowest_match(terms, nterms, "S"));

    printf("highest match %d\n", highest_match(terms, nterms, "S"));
    
    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "S");

    printf("%d\n", n_answer);

    for (int i = 0; i < n_answer; i++) {
        printf("%d %f %s\n", i, (answer)[i].weight, (answer)[i].term);
    }
    
    //free allocated blocks here -- not required for the project, but good practice
    free(terms);
    free(answer);

    return 0;
    
}
