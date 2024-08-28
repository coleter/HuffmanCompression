#ifndef __LINKEDLIST__
#define __LINKEDLIST__

#include "hcompress.h"
typedef struct node {
	tnode* value;
  	struct node* next;
} LinkedList;

LinkedList* llCreate();
int llIsEmpty(LinkedList* ll);
void llDisplay(LinkedList* ll);
void llAdd(LinkedList** ll, tnode* newValue);
void llFree(LinkedList* ll);
tnode* extractMin(LinkedList** ll);
void addInOrder(LinkedList** ll, tnode* v);
#endif

