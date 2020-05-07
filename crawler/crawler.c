/* Ryan Wu
 * cs50, May 2020
 * crawler.c
 */

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bag.h"
#include "hashtable.h"
#include "webpage.h"
#include "pagedir.h"

void crawler (bag_t *pages, hashtable_t *urls, int maxDepth, char *pageDir);

int main(int argc, char *argv[]) {
	//checking parameters
	if (argc!=4) {
		printf("Parameters not met: 3 arguments needed\n");
		return 1;
	}

	//parse the command line
	char *seedURL = argv[1];
	char *pageDir = argv[2];
	int maxDepth = atoi(argv[3]);
	
	//check if each argument works
	if (!NormalizeURL(seedURL) || !IsInternalURL(seedURL)){
		printf("Problem with the seed URL\n");
                return 2;
	}
	if (pageSaver(NULL, pageDir, 0)==false){
		printf("Directory does not exist\n");
                return 3;
	}
	if (maxDepth<0){
		printf("The max depth much be non-negative\n");
		return 4;
	}

	bag_t *webpages = bag_new();
	hashtable_t *URLs = hashtable_new(maxDepth+1);

	//seed webpage
	webpage_t *first = webpage_new(seedURL, 0, NULL);
	bag_insert(webpages, first);
	hashtable_insert(URLs, webpage_getURL(first), "");
	
	//webpage_delete(first);	
	crawler(webpages, URLs, maxDepth, pageDir);
	bag_delete(webpages, NULL);
	hashtable_delete(URLs, NULL);	
	return 0;
}

void crawler (bag_t *pages, hashtable_t *urls, int maxDepth, char *pageDir){
	int id=1;
	webpage_t *current = bag_extract(pages);
	while (current != NULL){
		if(pageFetcher(current)==false){
			 printf("Couldn't fetch html for page.\n");
		}
		if (pageSaver(current, pageDir, id)==false){
			 printf("Page failed to save.\n");
		}
                id++;
		if (webpage_getDepth(current)<maxDepth){
			if (pageScanner(pages, urls, current)==false){
				 printf("Page failed to scan.\n");
			}
		}
		current = bag_extract(pages);
	}
}
