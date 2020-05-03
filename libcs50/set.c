/* Ryan Wu cs50
 * April 2020
 * counters.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "memory.h"
#include <stdbool.h>

//local types
typedef struct setnode {
	const char *key;
	void *item;
	struct setnode *next;
} setnode_t;

//global types
typedef struct set {
	struct setnode *head;	
} set_t;


//global functions

set_t *set_new(void){
	set_t *set = count_malloc(sizeof(set_t));
	if (set==NULL){
		return NULL;
	}
	else {
		set->head=NULL;
		return set;
	}
}

bool set_insert(set_t *set, const char *key, void *item){
	if (set==NULL || key ==NULL || item==NULL) {
		return false;	
	}
	for (setnode_t *node = set->head; node != NULL; node = node->next) {
		if (node->key == key){
			return false;
		}
	}
	setnode_t *new=count_malloc(sizeof(setnode_t));
	new->key=key;
	new->item=item;
	if (new!=NULL){
		new->next = set->head;
		set->head=new;
		return true;
	}
	else{
		return false;
	}
}

void *set_find(set_t *set, const char *key){
	if (set!=NULL || key !=NULL){
		for (setnode_t *node = set->head; node != NULL; node = node->next) {
                	if (node->key == key){
				return node->item;
			}
		}
	}
	return NULL;
}

void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item) ){
	if (fp !=NULL){
		if (set!=NULL){
			fputc('{', fp);
			for (setnode_t *node = set->head; node != NULL; node = node->next) {
				if (itemprint!=NULL){
					fputc(' ', fp);
					(*itemprint)(fp, node->key, node->item);
				}
			}
			fputs("}\n", fp);
		}
		else {
                	fputs("(null)", fp);
       		}
	}
}

void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)){
	if (itemfunc !=NULL && set!=NULL){
		 for (setnode_t *node = set->head; node != NULL; node = node->next) {
			(*itemfunc)(arg, node->key, node->item); 
		 }
	}
}

void set_delete(set_t *set, void (*itemdelete)(void *item) ){
	if (set!=NULL){
		for (setnode_t *node = set->head; node != NULL; ) {
			if (itemdelete != NULL) {
				(*itemdelete)(node->item);
			}
			setnode_t *next = node->next;
			count_free(node);
			node=next;
		}
		count_free(set);
	}
}
