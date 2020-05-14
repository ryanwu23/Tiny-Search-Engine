/* Ryan Wu
 * cs 50, May 2020
 * word.c
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "word.h"

char *NormalizeWord (char *word){
	if (word != NULL){ //check if null
		for (int i = 0; word[i]!='\0'; i++){ //go through each letter
			if (word[i]>=65 && word[i]<=90){ //if uppercase
				word[i]=word[i]+32; //make lowercase
			}
		}	
	}
	return word;
}
