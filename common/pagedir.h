/* Ryan Wu
 * cs50, May 2020
 * pagedir.h
 */

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdbool.h>
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"

/* Retrives the html of the page and stores it in the page html */
bool pageFetcher(webpage_t *page);

/* Scans the page for urls. If url can be normalized, is internal and can be inserted into the hashtable, add the url page to bag */
bool pageScanner(bag_t *pages, hashtable_t *urls, webpage_t *page);

/* Saves the page to the given directory with given file number. Function also checks if pageDir exists if NULL is inputted as the page*/
bool pageSaver(webpage_t *page, char *pageDir, int file);

#endif
