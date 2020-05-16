#!/bin/bash

echo Testing the creation of index from ../crawler/wiki to output
./indexer ../crawler/wiki output
echo Using indexsort.awk to create output.sort
gawk -f indexsort.awk output>output.sort
echo Testing indextest by loading from output to output2
./indextest output output2
echo Using indexsort.awk to create output2.sort
gawk -f indexsort.awk output2>output2.sort
echo Files output.sort and output2.sort should be the same
echo Checking with cmp function. If nothing printed then output.sort and output2.sort are identical.
cmp output.sort output2.sort
echo Testing with non-existant directory
./indexer ./FAIL output
echo Testing with non-writtable file
./indexer ../crawler/wiki fail
echo Done testing
