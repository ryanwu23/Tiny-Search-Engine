/* Ryan Wu
 * cs 50, May 2020
 * indexer.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "hashtable.h"
#include "pagedir.h"
#include "webpage.h"
#include "index.h"


int main (int argc, char *argv[]) {
	//checking parameters
	if (argc!=3) {
		printf("Parameters not met: 2 arguments needed\n");
		return 1;
	}

	//parse the command line
	char *pageDir = malloc((strlen(argv[1]) + 1) * sizeof(char));
	strcpy(pageDir, argv[1]);
	if (pageSaver(NULL, pageDir, 0)==false){
		printf("Directory does not exist.\n");
		free(pageDir);
		return 2;
	}
	
	char *file = malloc((strlen(argv[2]) + 1) * sizeof(char));
	strcpy(file, argv[2]);
	FILE *fp;
        if ((fp = fopen(file, "w")) == NULL) {
		printf("File cannot be written.\n");
		free(pageDir);
		free(file);
		return 3;
        }	
	fclose(fp);

	//building the index
	hashtable_t *index = hashtable_new(100);
	if (index_build(pageDir, index)==false){
		printf("Index failed to be built.\n");
                hashtable_delete(index, (void (*)(void *))counters_delete);
                free(pageDir);
                free(file);
		return 4;
	}
	
	//saving the index to a file
	if (index_save(file, index) == false){
		printf("Index failed to be saved.\n");
                hashtable_delete(index, (void (*)(void *))counters_delete);
        	free(pageDir);
        	free(file);
		return 5;
	}
	
	//clean up
	hashtable_delete(index, (void (*)(void *))counters_delete);
	free(pageDir);
	free(file);
	return 0;
}
