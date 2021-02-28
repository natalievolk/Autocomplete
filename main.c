#include "autocomplete.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "test_cities.txt");

    
    printf("lowest match %d\n", lowest_match(terms, nterms, "Tor"));

    printf("highest match %d\n", highest_match(terms, nterms, "Tor"));
    
    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "Tor");

    printf("%d\n", n_answer);
    

    //free allocated blocks here -- not required for the project, but good practice
    return 0;
    
}
