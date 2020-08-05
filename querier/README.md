## Querier
`querier.c`

### Usage
To use the querier, you need to run with with it two arguments. The first is the pageDir that was outputted by crawler. The second is the file with the index outputted by indexer.

```
querier pageDir fileName
```

For example:
```
querier ../crawler/wiki ../indexer/output
```

### Implementation
In IMPLEMENTATION.md

### Assumptions
Assumed that inputted query doesn't have extra spaces nor any disallowed characters.

### Compilation
To compile first run `make` in the common library to create `common.a`.
Run `make` in querier directory to make runnable file used by `./querier`.
To simply test with testing.sh, use `make test`.
