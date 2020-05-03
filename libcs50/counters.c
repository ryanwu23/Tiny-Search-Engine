/* Ryan Wu cs50
 * April 2020
 * counters.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "memory.h"

//Local types
typedef struct countersnode{
	int key;
	int value;
	struct countersnode *next;
} countersnode_t;

//Global types
typedef struct counters {
	struct countersnode *head;
} counters_t;


//Global functions

counters_t *counters_new(void) {
	counters_t *counters = count_malloc(sizeof(counters_t));
	if (counters == NULL){
		return NULL;
	}
	else {
		counters->head = NULL;
		return counters;
	}
}

int counters_add(counters_t *ctrs, const int key){
	if (ctrs ==NULL || key<0){
		return 0;
	}
	for (countersnode_t *node = ctrs->head; node !=NULL; node = node->next){
		if (node->key==key){
			node->value++;
			return node->value;
		}
	}
	countersnode_t *new= count_malloc(sizeof(countersnode_t));;
	new->key=key;
	new->value=1;
	if (new!=NULL){
		new->next = ctrs->head;
		ctrs->head= new;
		return 1;
	}
	return 0;
}

int counters_get(counters_t *ctrs, const int key){
	if (ctrs ==NULL || key<0){
                return 0;
        }
	for (countersnode_t *node = ctrs->head; node !=NULL; node = node->next){
                if (node->key==key){
                        return node->value;
                }
        }
	return 0;
}

bool counters_set(counters_t *ctrs, const int key, const int count){
 	if (ctrs ==NULL || key<0 || count<0){
                return false;
        }
	for (countersnode_t *node = ctrs->head; node !=NULL; node = node->next){
                if (node->key==key){
                        node->value=count;
                        return true;
                }
        }
        countersnode_t *new= count_malloc(sizeof(countersnode_t));;
        new->key=key;
        new->value=count;
        if (new!=NULL){
                new->next = ctrs->head;
                ctrs->head= new;
        }
        return true;
}

void counters_print(counters_t *ctrs, FILE *fp){
	if (fp != NULL){
		if (ctrs !=NULL) {
			fprintf(fp, "{");
			for (countersnode_t *node = ctrs->head; node !=NULL; node = node->next){
				if (node==ctrs->head){
					fprintf(fp, "%i=%i", node->key, node->value);
				}
				else {
					fprintf(fp, ", %i=%i", node->key, node->value);
				}
			}
			fprintf(fp, "}\n");
		}
		else {
			fprintf(fp, "null\n");
		}
	}
}

void counters_iterate(counters_t *ctrs, void *arg, void (*itemfunc)(void *arg, const int key, const int count)){
	if (itemfunc != NULL && ctrs !=NULL){
		for (countersnode_t *node = ctrs->head; node !=NULL; node = node->next){
			(*itemfunc)(arg, node->key, node->value);
		}
	}
}

void counters_delete(counters_t *ctrs){
	if (ctrs !=NULL){
		for (countersnode_t *node = ctrs->head; node !=NULL; ){
			countersnode_t *holder=node->next;
			count_free(node);
			node=holder;
		}
		count_free(ctrs);
	}
}
