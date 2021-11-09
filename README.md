# Autocomplete

This is a rapid implementation of the autocomplete functionality. It uses quicksort to sort thousands of terms in lexicographic order, and then binary search to find the all terms that match the query word. All matches are then sorted by their weight, to find the top guess for the autocompletion of the query word.