#!/bin/bash
echo Testing letters to depth 4 saved in letters dir
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html ./letters 4

echo Testing wikipedia to depth 1 saved in wiki dir
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/ ./wiki/ 1

echo Testing with non-internal url
./crawler https://www.google.com/ ./letters 1

echo Testing with non-existent directory
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html ./notreal 2

echo Testing with negative depth
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html ./letters -1

echo Testing toscrape to depth 0 saved in toscrape dir
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/toscrape/index.html ./toscrape 0

