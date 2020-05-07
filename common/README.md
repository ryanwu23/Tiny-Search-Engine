# CS50 Lab 4
## Ryan Wu, CS50 Spring 2020

### Common Library for TSE

### Usage
Run `make` in order to create `common.a` and `make clean` to clean.

### pageDir functions
```c
/* Retrives the html of the page and stores it in the page html */
bool pageFetcher(webpage_t *page);

/* Scans the page for urls. If url can be normalized, is internal and can be inserted into the hashtable, add the url page to bag */
bool pageScanner(bag_t *pages, hashtable_t *urls, webpage_t *page);

/* Saves the page to the given directory with given file number. Function also checks if pageDir exists if NULL is inputted as the page*/
bool pageSaver(webpage_t *page, char *pageDir, int file);
```
