#include <stdio.h>
#include <stdlib.h> // for malloc
#include "linkedList.h"

//prototype functions

LinkedList* llCreate() {
	return NULL;
}

int llIsEmpty(LinkedList* ll) {
  	return (ll == NULL);
}


void llDisplay(LinkedList* ll) { 
  	LinkedList* p = ll;
  	printf("[");  
  	while (p != NULL) {
   		printf("%c : %d ", (char)(p->value->c), p->value->frequency);
    		p = p->next;
  	}

 	 printf("]\n");
}


void llAdd(LinkedList** ll, tnode* newValue) {

	// Create the new node
  	LinkedList* newNode = (LinkedList*) malloc(1 * sizeof(LinkedList)); 
  	newNode->value = newValue;
 	newNode->next = NULL; 
  
 	//Find where new node is inserted
  	LinkedList* p = *ll;

	//if the list is empty
  	if (p == NULL) {  // Add first element
		//newNode becomes the head of the list
    		*ll = newNode;  // This is why we need ll to be a **

  	} else {
    		while (p->next != NULL) {
      			p = p->next;
    		}
   	// Attach it to the end
    	p->next = newNode;
  	}
}
//deletes the entire tree
void llFree(LinkedList* ll) {
  	LinkedList* p = ll;
  	while (p != NULL) {
    		LinkedList* oldP = p;
    		p = p->next;
    		free(oldP);
  	}
}

void addInOrder(LinkedList** ll, tnode* newValue) {
	LinkedList* newNode = (LinkedList*) malloc (1 * sizeof(LinkedList));
	newNode->value = newValue;
	newNode->next = NULL;

	LinkedList* temp = *ll;
	
	if (temp == NULL) {
		*ll = newNode;
		return;
	}

	if (newNode->value->frequency < temp->value->frequency) {
		
		newNode->next = temp;
		*ll = newNode;
		return;
	}	
	
	//while the frequency that temp is pointing to is bigger or while the temp.next is empty
	while ( temp->next != NULL && newValue->frequency > temp->next->value->frequency) {
		//advance temp pointer (to a linkedlist node)
		temp = temp->next;
	}
	
	newNode->next = temp->next;
	temp->next = newNode;

}

tnode* extractMin(LinkedList** ll) {
	//*head is a pointer to the first node
	LinkedList* head = *ll;

	//tnode* value is the value of the first node that is being extracted
	tnode* value = head->value;

	//make the pointer that was passed to us
	//point to the next node after the first one
	*ll = head->next;

	//free
	free(head);

	return value;
}
/*
int main() {
  
  	LinkedList* l = llCreate();
  	llDisplay(l);

  	tnode n1;
	n1.c = 97;
	n1.frequency = 97;

	tnode n2;
        n2.c = 98;
	n2.frequency = 98;
	

	
	tnode n3;
        n3.c = 99;
	n3.frequency = 99;
	


	
	tnode n4;
        n4.c = 100;
	n4.frequency = 100;
	


	tnode n5;
        n5.c = 101;
	n5.frequency = 101;


	addInOrder(&l, &n3);
	llDisplay(l);
	
	addInOrder(&l, &n1);
	llDisplay(l);
	
	addInOrder(&l, &n2);
	llDisplay(l);
	
	addInOrder(&l, &n4);
	llDisplay(l);
		
	
	//printf("%c\n", extractMin(&l)->c);
	//llDisplay(l);
  	llFree(l);

}*/
