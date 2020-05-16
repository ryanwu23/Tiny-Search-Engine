# CS50 tse Indexer
## Ryan Wu, CS50 Spring 2020

### Implementation
indexer.c holds function `main`.

index.c holds functions `index_build`, `index_save` and `index_load`.

### Data Structures
The data structure used to hold an index is a hashtable that holds the word and counters for each document.

hashtable holds a bunch of sets which words get hashed to. Each item in the set has a key, which holds the word, and the item, which holds a counters data structure. Each counter has the key as the docID and count of the word apparence in that doc.

hashtable_t, set_t, counters_t.

### Exit Status
0 - success\
1 - 2 arguments weren't entered\
2 - Directory inputted does not exist.\
3 - File inputted cannot be written.\
4 - Index failed to be build.\
5 - Index failed to be saved.\
