# CS50 Lab 4
## Ryan Wu, CS50 Spring 2020

### Implementation
crawler.c holds functions `main` and `crawler`.

`main` handles error cases, creates the bag and hashtable and calls `crawler.

`crawler` loopes over each page calling functions from `pageDir` to get each page, scan it, and save it to the directory.

### Exit Status
0 - success
1 - 3 arguments weren't entered
2 - url can't be normalized or isn't internal
3 - directory doesn't exist or isn't readable
4 - maxDepth is negative

