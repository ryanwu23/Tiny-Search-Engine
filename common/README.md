# CS50 Lab 4
## Ryan Wu, CS50 Spring 2020

### Common Library for TSE

### Usage
Run `make` in order to create `common.a` and `make clean` to clean.

### pageDir.c functions
```c
/* Retrives the html of the page and stores it in the page html */
bool pageFetcher(webpage_t *page);

/* Scans the page for urls. If url can be normalized, is internal and can be inserted into the hashtable, add the url page to bag */
bool pageScanner(bag_t *pages, hashtable_t *urls, webpage_t *page);

/* Saves the page to the given directory with given file number. Function also checks if pageDir exists if NULL is inputted as the page*/
bool pageSaver(webpage_t *page, char *pageDir, int file);
```

### index functions
```c
/* Helper function that adds each file into the index*/
bool build_helper(char *file, hashtable_t *index, int id);

/* Build function which goes through each file in the dir and adds it to index*/
bool index_build (char *pageDir, hashtable_t *index);

/* Function called in counters_iterate from hashtablefunc to print key, count pairs*/
void countersfunc(void *arg, const int key, const int count);

/* Function called in hashtable_iterate from index_save to print word and call countersfunc*/
void hashtablefunc(void *arg, const char *key, void *item);

/* Iterates through each entry in the hashtable and saves output to a file*/
bool index_save (char *file, hashtable_t *index);

/* Takes a file that has an index and loads it into a index data structure*/
bool index_load(char *file, hashtable_t *index);
```

### word function
```c
/* This function takes a word and normalizes it by making it all lowercase*/
char *NormalizeWord (char *word);
```

