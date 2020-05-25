/* Ryan Wu
 * cs 50, May 2020
 * index.c
 */
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

bool build_helper(char *file, hashtable_t *index, int id){
        //check file
	FILE *fp;
        if ((fp = fopen(file, "r")) == NULL) {
                return false;
        }

        //get url, maxdepth and html for the webpage
        char *url = freadlinep(fp);
	char *stringdepth = freadlinep(fp); // this line needed to free the allocated memory
        int maxDepth = atoi(stringdepth);
        char *html = freadfilep(fp);
	free(stringdepth);
        fclose(fp);
        webpage_t *page = webpage_new(url, maxDepth, html);

        //go through each word in the file and add it to the hashtable
        int pos =0;
        char *result;
        while ((result = webpage_getNextWord(page, &pos)) != NULL) {
                if (strlen(result)>2){
                        NormalizeWord(result);
			if (hashtable_find(index, result) == NULL){
                                counters_t *insert = counters_new();
                                hashtable_insert(index, result, insert);
                        }
                        counters_add(hashtable_find(index, result), id);
		}
                free(result);
        }
	webpage_delete(page);
	return true;
}

bool index_build (char *pageDir, hashtable_t *index){
	char path[100]="";
        int file =1;
	//creating the dir/file pathway
	sprintf(path, "%s/%d", pageDir, file);
	FILE* fp;
	//while loop for each file in dir
	while ((fp = fopen(path, "r")) != NULL){
		fclose(fp);
		//calls helper function that updates index with each file
		if (build_helper(path, index, file)==false){
			return false;
		}
		
		//setting up for the rest of the while loop
		FILE* fp;	
		file++;
		sprintf(path, "%s/%d\0", pageDir, file);
	}
	return true;
}

void countersfunc(void *arg, const int key, const int count) {//helper function for index save
	FILE *fp = arg;
	fprintf(fp, " %d %d", key, count);
}

void hashtablefunc(void *arg, const char *key, void *item){//helper function for index save
	FILE *fp = arg;
	counters_t *counter=item;
	fprintf(fp, "%s ", key);
	counters_iterate(counter, fp, countersfunc);
	fprintf(fp, "\n");
}

bool index_save (char *file, hashtable_t *index){
	//check file
	FILE *fp;
        if ((fp = fopen(file, "w")) == NULL) {
                return false;
        }
	//iterate through the hashtable and print to file
	hashtable_iterate(index, fp, hashtablefunc);
	fclose(fp);	 	
	return true;
}

bool index_load(char *file, hashtable_t *index){
	//checking if file can be opened
	FILE *fp;
        if ((fp = fopen(file, "r")) == NULL) {
                return false;
        }
	
	//creating variables
	char *word;
	int doc;
	int count;
	while((word = freadwordp(fp)) !=NULL){//start each line by getting the word
		//create new counter with that word
		counters_t *insert=counters_new();
		hashtable_insert(index, word, insert);
		while (fscanf(fp, "%d %d ", &doc, &count) == 2) {//while you can succesfully get two ints, insert into the index
     			counters_set(hashtable_find(index, word), doc, count);
    		}
		free(word);
	}
	fclose(fp);
	return true;
}
