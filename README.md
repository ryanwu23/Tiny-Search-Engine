# Ryan Wu
## Tiny Search Engine Project

This is a tiny search engine which has 3 core components.\
1. The crawler which takes in a webpage and crawls through the getting all the pages linked from the initial page.\
2. An indexer that takes those pages and counts and stores page # rankings based off of word appearance. These word-page ranking pairs are stored in a hashtable filled with sets data structure.\
3. A querier which given an inputed querier, will parse through the query and print out a ranked list of the urls and pages where the search is most applicable.

To build, run `make`.

To clean up, run `make clean`.
