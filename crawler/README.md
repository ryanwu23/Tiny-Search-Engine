# CS50 Lab 4
## Ryan Wu, CS50 Spring 2020

### Crawler
`crawler.c` crawls a website and retrieves webpages starting with a specified URL.

### Usage
To use crawler, you need to run it with 3 additional arguments. The first is the starting url. The second is the directory where the pages will be saved. The third is the max depth that the crawler will explore.

`./crawler seedURL pageDir maxDepth`

### Implementation
In IMPLEMENTATION.md

### Assumptions
No assumptions beyond those that are clear from the spec.

### Compilation
To compile first run `make` in the common library to create `common.a`.
Run `make` in crawler directory to make runnable file used by `./crawler`.
To simply test with testing.sh, use `make test`.
