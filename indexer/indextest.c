/* Ryan Wu
 * cs 50, May 2020
 * indextest.c
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
        char *oldindex = malloc((strlen(argv[1]) + 1) * sizeof(char));
        strcpy(oldindex, argv[1]);
	
	FILE *fp;
        if ((fp = fopen(oldindex, "r")) == NULL) {
                printf("File with index cannot be read.\n");
                free(oldindex);
                return 2;
        }
	fclose(fp);

	char *newindex = malloc((strlen(argv[2]) + 1) * sizeof(char));
        strcpy(newindex, argv[2]);
        FILE *fp2;
        if ((fp2 = fopen(newindex, "w")) == NULL) {
                printf("File for new index cannot be written.\n");
                free(oldindex);
                free(newindex);
                return 3;
        }
	fclose(fp2);

	//loading the index from a file
	hashtable_t *index = hashtable_new(100);
	if (index_load(oldindex, index)==false){
		printf("Index failed to be loaded.\n");
                free(oldindex);
                free(newindex);
                hashtable_delete(index, (void (*)(void *))counters_delete);
		return 4;
	}
	//saving the index to a file
	if (index_save(newindex, index) == false){
                printf("Index failed to be saved.\n");
                hashtable_delete(index, (void (*)(void *))counters_delete);
                free(oldindex);
        	free(newindex);
		return 5;
        }

        //clean up
        hashtable_delete(index, (void (*)(void *))counters_delete);
        free(oldindex);
        free(newindex);
	return 0;
}
