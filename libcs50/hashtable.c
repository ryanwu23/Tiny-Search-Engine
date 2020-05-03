/* Ryan Wu cs50
 * April 2020
 * hashtable.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "hashtable.h"
#include "memory.h"
#include "jhash.h"
#include "set.h"

//Global type
typedef struct hashtable{
	int num_slots;
	set_t **slot;       
} hashtable_t;

//Global functions

hashtable_t *hashtable_new(const int num_slots){
	hashtable_t *hashtable = count_malloc(sizeof(hashtable_t));
	if (hashtable == NULL){
		return NULL;
	}
	else {
		hashtable->num_slots=num_slots;
		hashtable->slot=calloc(num_slots, sizeof(set_t*));
		for(int i =0; i<num_slots; i++){
			hashtable->slot[i]=set_new();
		}
		return hashtable;
	}
}

bool hashtable_insert(hashtable_t *ht, const char *key, void *item){
	if (ht!=NULL && key!=NULL && item !=NULL){
		int hash = JenkinsHash(key, ht->num_slots);
		return set_insert(ht->slot[hash], key, item);
	}
	return false;
}

void *hashtable_find(hashtable_t *ht, const char *key){
	if (ht!=NULL && key!=NULL){
                int hash = JenkinsHash(key, ht->num_slots);
                return set_find(ht->slot[hash], key);
        }
        return NULL;
}

void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)){
	if (fp!=NULL){
		if (ht!=NULL){
			for (int i=0; i<ht->num_slots; i++){
				if (itemprint != NULL) {
					set_print(ht->slot[i], fp, itemprint);
				}
				fprintf(fp, "\n");
			}
		}
		else{
			fprintf(fp, "(null)");
		}
	}

}

void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item) ){
	if (ht!=NULL){
		for (int i=0; i<ht->num_slots; i++){
                        if (itemfunc != NULL) {
				set_iterate(ht->slot[i], arg, itemfunc);
			}
		}
	}
}

void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) ){
	if (ht!=NULL){
		for (int i=0; i<ht->num_slots; i++){
                        if (itemdelete != NULL) {
				set_delete(ht->slot[i], itemdelete);
			}
		}
		free(ht->slot);
		free(ht);
	}
}
