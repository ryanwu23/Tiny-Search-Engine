# CS50 tse Querier
## Ryan Wu, CS50 Spring 2020

### User Interface
The Querier's only interface with the user is on the command-line; it must always have two arguments.

```
querier pageDir fileName
```

For example:
```
querier ../crawler/wiki ../indexer/output
```

### Inputs and Outputs
Input: Inputs are command line parameters, a directory created by crawler, and a file with an index created by indexer.
After that, inputs come from the stdin.

Output: querier takes each query request and creates scores for each document containing those words. Then it prints the scores in a decreasing order by giving the score, the docId and then the link to the webpage.

### Functional decomposition into modules
We anticipate the following modules or functions:
1. main - parses the command line and calls other functions
2. querier - asks for input from stdin and loops until EOF
3. checkquery - checks for error cases
4. parsequery - takes a query and parse it into section and does the math to get scores
5. printquery - takes the scores from parsequery and prints them


### Pseudo code for logic/algorithmic flow
1. Parse the commond like and check that each argument is good
2. Take in inputs for the query
	1. Parse each query
	2. Check for error cases
	3. Find scores for and cases
	4. Finish scores with or cases
	5. Rank scores
	6. Print out scores
3. continue until EOF

### Dataflow through modules
1. main parses parameters and passes it to querier
2. querier takes inputs for stdin and checks with querycheck and then calls parsequery
3. checkquery is called in querier and checks for erros
4. parsequery takes the query and gets the scores which are passed onto printquery
5. printquery prints the scores and documents

### Major data structures
Three helper modules provide data structures:
1. counters of docID and count of word
2. set of words and counters (indirectly used by hashtable)
3. hashtable of words

### Testing plan
A small test program in testing.sh to test each module to make sure it does what it's supposed to do
Uses fuzzquery.c to test lots of inputs.
