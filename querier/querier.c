/* Ryan Wu
 * cs 50, May 2020
 * querier.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "hashtable.h"
#include "pagedir.h"
#include "webpage.h"
#include "index.h"
#include "word.h"

void querier (char *pageDir, hashtable_t *index);

bool checkquery(char *words[], int size);

void parsequery(char *pageDir, hashtable_t *index, char *words[], int size);

void printquery(char *pageDir, int scores[], int numfile);

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
        if ((fp = fopen(file, "r")) == NULL) {
                printf("File cannot be opened.\n");
                free(pageDir);
                free(file);
                return 3;
        }
	fclose(fp);

	//loading the index from a file
        hashtable_t *index = hashtable_new(100);
        if (index_load(file, index)==false){
                printf("Index failed to be loaded.\n");
                free(file);
                hashtable_delete(index, (void (*)(void *))counters_delete);
                return 4;
        }
	querier(pageDir, index);
	return 0;
}

void querier (char *pageDir, hashtable_t *index){
	char *line;
	printf("Query? ");
	while ((line = freadlinep(stdin)) != NULL) {
		printf("Query: %s\n", line);
		
		//parsing the line
		char *words[strlen(line)/2];
		words[0]=line;
		int holder=1;
		for (char *p = line; *p != '\0'; p++) {
			if (*p==' '){
				*p='\0';
				p++;
				words[holder]=p;
				holder++;
			}
		}
		//normalizing each word from the line
		for (int i=0; i<holder; i++){
			words[i]=NormalizeWord(words[i]);
		}

		if (checkquery(words, holder)){
			parsequery(pageDir, index, words, holder);
		}
		printf("Query? ");

	}
}

bool checkquery(char *words[], int size){
	//checks for error cases
	if (strcmp(words[0], "and")==0){
		printf("Error: 'and' cannot be first.\n");
		return false;
	}
	if (strcmp(words[0], "or")==0){
		printf("Error: 'or' cannot be first.\n");
		return false;
	}
	if (strcmp(words[size-1], "and")==0){
                printf("Error: 'and' cannot be last.\n");
                return false;
        }
        if (strcmp(words[size-1], "or")==0){
                printf("Error: 'or' cannot be last.\n");
                return false;
        }
	for (int i=0; i<size; i++){
		if (i+1<size && (strcmp(words[i], "and")==0 || strcmp(words[i], "or")==0) &&(strcmp(words[i+1], "and")==0 || strcmp(words[i+1], "or")==0)){
			printf("Error: '%s' and '%s' cannot be adjacent.\n", words[i], words[i+1]);
			return false;
		}
	}
	return true;
}

void parsequery(char *pageDir, hashtable_t *index, char *words[], int size){
	//this code is to cound the number of files in the directory
	FILE* fp;
	int numfile=1;
	char path[100]="";
        sprintf(path, "%s/%d", pageDir, numfile);
	while ((fp = fopen(path, "r")) != NULL){
		numfile++;
		sprintf(path, "%s/%d", pageDir, numfile);
	}
	numfile--;
	
	//create an array of scores, one for each document
	int scores[numfile+1];
	for (int i=1; i<=numfile; i++){
                sprintf(path, "%s/%d", pageDir, i);
		fp = fopen(path, "r");
		scores[i]=0;
	}

	//creat an array to hold the order
	int order [numfile][size];
	for (int i=1; i<=numfile; i++){
		for (int j=0; j<size; j++){
			if (strcmp(words[j], "and")==0){
				 order[i][j]=-1;
			}
			else if (strcmp(words[j], "or")==0){
				 order[i][j]=-2;
			}
			else{	
				order[i][j]=counters_get(hashtable_find(index, words[j]), i);
			}
		}
	}
		
	//creating array to hold scores for and
	int holder=0;
	for (int i=0; i<size; i++){
		if (strcmp(words[i], "and")==0){
			holder+=2;
		}
		if (i!=0){
			if (strcmp(words[i], "and")!=0 && strcmp(words[i], "or")!=0 && strcmp(words[i-1], "and")!=0 && strcmp(words[i-1], "or")!=0){
				holder++;
			}
		}
	}
	int andorder[numfile][size-holder];
	
	//putting the scores in for and
	for (int i=1; i<=numfile; i++){
		int pos=0;
		 for (int j=0; j<size; j++){
			if (order[i][j]==-1){
				if (order[i][j-1]<order[i][j+1]){
					andorder[i][pos]=order[i][j-1];
					order[i][j+1]=andorder[i][pos];
				}
				else{
					andorder[i][pos]=order[i][j+1];
				}
				pos++;
			}
			else if (order[i][j]==-2){
				andorder[i][pos]=-2;
				pos++;
			}
			else if (j+1<size && order[i][j]!=-1 && order[i][j]!=-2 && order[i][j+1]!=-1 && order[i][j+1]!=-2){
				if (order[i][j+1]<order[i][j]){
        				andorder[i][pos]=order[i][j+1];
                                }
                                else{
                                        andorder[i][pos]=order[i][j];
                                	order[i][j+1]=andorder[i][pos];
				}
				pos++;
			}
			else if ((j==0 || order[i][j-1]==-1 || order[i][j-1]==-2) && order[i][j+1]!=-1) {
				andorder[i][pos]=order[i][j];
				pos++;
			}
		 }

	}

	//getting the final scores with or
	for (int i=1; i<=numfile; i++){
		int total=0;
		for (int j=0; j<size-holder; j++){
			if (andorder[i][j]!=-2){
				total+=andorder[i][j];
			}
		}
		scores[i]=total;
	}
	printquery(pageDir, scores, numfile);

}


void printquery(char *pageDir, int scores[], int numfile){
	int highest=-1;
	int highid=-1;
	int remain=numfile;
	int matches=0;
	//find how many docs match
	for (int i=1; i<=numfile; i++){
		if (scores[i]!=0){
			matches++;
		}
	}
	if (matches==0){ //if not matches
		printf("No documents match.\n");
	}
	else{ //print the matches
		printf("Matches %d documents (ranked):\n", matches);
		while (highest!=0 && remain!=0){
			for (int i=1; i<=numfile; i++){
				if (scores[i]>highest){
					highest=scores[i];
					highid=i;
				}
			}
			if (highest!=0){
				//printint everything in the line
				FILE *fp;
				char path[100]="";
				sprintf(path, "%s/%d", pageDir, highid);
                		fp = fopen(path, "r");
				char *url= freadlinep(fp);
				printf("score\t%d\tdoc\t%d: %s \n", scores[highid], highid, url);
				scores[highid]=0;
				free(url); 
				highest=-1;
			}
			remain--;
		}
	}
	printf("-----------------------------------------------\n");
}
