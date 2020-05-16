# CS50 Lab 5
## Ryan Wu, CS50 Spring 2020

### Indexer
`indexer.c` reads from documents from a directory and builds an inverted index mapping from words to documents, and writes that index to a file.

### Usage
To use the indexer, you need to run with with it two arguments. The first is the pageDir that was outputted by crawler. The second is the file where the index will be saved.

```
indexer pageDir fileName
```

For example:
```
indexer ../crawler/data testfile
```

### Implementation
In IMPLEMENTATION.md

### Assumptions
No assumptions beyond those that are clear from the spec.

### Compilation
To compile first run `make` in the common library to create `common.a`.
Run `make` in crawler directory to make runnable file used by `./indexer`.
To simply test with testing.sh, use `make test`.
