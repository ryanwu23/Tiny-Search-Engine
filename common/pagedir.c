/* Ryan Wu
 * cs50, Spring 2020
 * pagedir.c
 */

#include <stdio.h>
#include <string.h>
#include "pagedir.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/webpage.h"

bool pageFetcher(webpage_t *page){
	return webpage_fetch(page);
}

bool pageScanner(bag_t *pages, hashtable_t *urls, webpage_t *page){
	int pos = 0;
	char *url;
	printf("Page explored: %s\n", webpage_getURL(page));
	while ((url= webpage_getNextURL(page, &pos)) != NULL){
		printf("Url found: %s\n", url);
		if (NormalizeURL(url) && IsInternalURL(url) && hashtable_insert(urls, url, "")){
			webpage_t *newpage = webpage_new(url, webpage_getDepth(page)+1, NULL);
			bag_insert(pages, newpage);
		}
	}
	return true;
}

bool pageSaver(webpage_t *page, char *pageDir, int file){
	FILE* fp;
	char path[100]="";
        //creating path with dir and file
	sprintf(path, "%s/%d", pageDir, file);
	
	//if page is null, program checks if the dir exists
	if (page==NULL){
		if ((fp = fopen(path, "w")) == NULL){
			return false;
		}
		else{
			fclose(fp);
			remove(path);
			return true;
		}
	}

	//if page is give, that page is saved
	if ((fp = fopen(path, "w")) == NULL) {
		return false;
	}
	fprintf(fp, "%s\n", webpage_getURL(page));
	fprintf(fp, "%d\n", webpage_getDepth(page));
	fprintf(fp, "%s\n", webpage_getHTML(page));
	fclose(fp);
	return true;
}
