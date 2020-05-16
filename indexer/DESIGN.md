# CS50 tse Indexer
## Ryan Wu, CS50 Spring 2020

### User Interface
The Indexer's only interface with the user is on the command-line; it must always have two arguments.

```
indexer pageDir fileName
```

For example:
```
indexer ../crawler/data testfile
```

### Inputs and Outputs
Input: Inputs are command line parameters and a directory created by crawler.

Output: indexer creates a file that contains the inverted data structure. Each line has the word then pairs of the file id number and the count of number of times that word appeared.

### Functional decomposition into modules
We anticipate the following modules or functions:

1. main, which parses arguments and calls the other functions
2. pageSaver, which checked whether the directory exists
3. index_build, which builds the index by reading from the directory
4. build_helper, which reads in a file and adds it to the index
5. index_save, which saves the index to a file
6. hashtablefunc, which is called to help print into a file
7. counterfunc, which is also called to help print into a file
8. index_load, which takes a file with an index and loads it into a data structure
9. NormalizeWord, which takes a word and makes it all lowercase

And some helper modules that provide data structures:

1. hashtable of words and counters
2. counters with the id of doc and the count of words

### Pseudo code for logic/algorithmic flow
1. Parse the command line and check to make sure each argument is good
2. While there are files left in pageDir
	1. Turn each file into a webpage
	2. Use webpage function to go through each word
		1. Normalize word if larger than 2 characters
		2. Check if word is in hashtable
			1. if not add the word
		3. use counters_add to increment
4. iterate through the hashtable
	1. print each word and id, count pairs
5. clean up by deleting hashtable and freeing other alocated memory.

### Dataflow through modules
1. main parses the parameters then passes it to index_build and then to index_save
2. index_build takes in a directory and for each file, it calls build_helper
3. build_helper takes the file from index_build and add's its information to the index
4. index_save takes the target file and calls it's iterate functions to print the index into that file
5. index_load takes in a target file and extracts the data to add to an index data structure
6. NormalizeWord takes in a word and returns that word in all lowercase

### Major data structures
Three helper modules provide data structures:
1. counters of docID and count of word
2. set of words and counters (indirectly used by hashtable)
3. hashtable of words

### Testing plan
A small test program in testing.sh to test each module to make sure it does what it's supposed to do

1. Testing indexer.c by testing a directory from crawler
2. sort the resulting output
3. Testing indextest.c by loading the output from test in 1
4. sort that output
5. compare the sorted outputs from 2 and 4 to see if they are the same
6. test non-existant directory
7. test a file that cannot be written

