/* Ryan Wu
 * cs 50, May 2020
 * index.h
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/counters.h"
#include "../libcs50/hashtable.h"
#include "pagedir.h"
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"
#include "word.h"
#include "index.h"

/* Helper function that adds each file into the index*/
bool build_helper(char *file, hashtable_t *index, int id);

/* Build function which goes through each file in the dir and adds it to index*/
bool index_build (char *pageDir, hashtable_t *index);

/* Function called in counters_iterate from hashtablefunc to print key, count pairs*/
void countersfunc(void *arg, const int key, const int count);

/* Function called in hashtable_iterate from index_save to print word and call countersfunc*/
void hashtablefunc(void *arg, const char *key, void *item);

/* Iterates through each entry in the hashtable and saves output to a file*/
bool index_save (char *file, hashtable_t *index);

/* Takes a file that has an index and loads it into a index data structure*/
bool index_load(char *file, hashtable_t *index);

#endif // __INDEX_H
