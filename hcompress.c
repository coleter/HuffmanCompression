#include <stdio.h>
#include <string.h>
#include <math.h>
#include "hcompress.h"
#include <stdlib.h>
#include "linkedList.h"

int main(int argc, char *argv[]) {
  // Check the make sure the input parameters are correct
  if (argc != 3) {
    printf("Error: The correct format is \"hcompress -e filename\" or \"hcompress -d filename.huf\"\n");
    fflush(stdout);
    exit(1);
  }
  // Create the frequency table by reading the generic file
  tnode* leafNodes = createFreqTable("decInd.txt");

  // Create the huffman tree from the frequency table
  tnode* treeRoot = createHuffmanTree(leafNodes);
  if (strcmp(argv[1], "-e") == 0) {
    // Pass tthe leafNodes since it will process bottom up
    encodeFile(argv[2], leafNodes);
  }
  else {
    // decode
    // Pass the tree root since it will process top down
    decodeFile(argv[2], treeRoot);
  }
  //free tree
  free(leafNodes);
  return 0;
}

tnode* createFreqTable(char* text){
  //allocate a table for ASCII (size 128) of type tnode*
  tnode* table = (tnode*)malloc(128 * sizeof(tnode));
  //each tnode* will have frequency = 0 initially and they are all leaf nodes
  int i;
  for (i = 0; i < 128; i++) {
    table[i].frequency = 0;
    table[i].isLeaf = 1;
  }
  //open file for reading, read one character at a time
  FILE* file;
  int ch;
  file = fopen(text, "r");
  if (file == NULL) {
    printf("file can't be opened \n");
  }
  ch = fgetc(file);
  //while ch is not the termination character
  while (ch != EOF) {
    table[ch].frequency++;
    table[ch].c = ch;
    ch = fgetc(file);
  }
  fclose(file);
  return table;
}

tnode* createHuffmanTree(tnode* nodes){
  LinkedList* pq = NULL;
  int count = 0;  
  nodes['\0'].frequency += 1;
  //Add all nodes to priority queue
  for (int i = 0; i < 128; i++) {
    if (nodes[i].frequency > 0){
      addInOrder(&pq, &nodes[i]);
      count++;
    }
  }
  
  for (int i = 0; i < count-1; i++) {
    tnode* parent = (tnode*)malloc(sizeof (tnode));
    tnode* left = extractMin(&pq);
    tnode* right = extractMin(&pq);
    parent->left = left;
    parent->right = right;
    left->parent = parent;
    right->parent = parent;
    parent->frequency = (left->frequency) + (right->frequency);
    addInOrder(&pq, parent);
  }
  tnode* root = extractMin(&pq);
  root->parent = NULL;
  return root;
}

void encodeFile(char* input, tnode* nodes){
  //a loop that goes through each character in the text file
  FILE* in;
  in = fopen(input, "r");
  FILE* out;
  char fileName[strlen(input) + 5];
  const char* extension = ".huf";
  strcpy(fileName, input);
  strcpy(fileName+strlen(input), extension);
  out = fopen(fileName, "w+");
  if (in == NULL) {
    printf("input file can't be opened \n");
  }
  if (out == NULL) {
    printf("output file can't be opened\n");
  }
  char c = fgetc(in);
  //this variable tells me which bit I am setting
  int bitToSet = 7;
  tnode* node = NULL;
  //create an empty byte that has 8 bits and fill them with 0's
  byte byteToWrite = 0;
  //This variable is used to encode a single letter from file then written to bytesToWrite in reverse order
  while (c != EOF) {
    node = &nodes[(unsigned char)c];
    encodeCharacter(node, &byteToWrite, &bitToSet, out);
    //increment numberOfBits and write to file and reset if it reaches 8
    c = fgetc(in);
}
  //Encode the terminating character
  node = &nodes['\0'];
  encodeCharacter(node, &byteToWrite, &bitToSet, out);
  if(bitToSet != 7){
    fputc(byteToWrite, out);
  }
  fclose(in);
  fclose(out);
}

void encodeCharacter(tnode* node, byte* byteToWrite, int* bitToSet, FILE* out){
  //encodes the entire letter code
  int i = 0;
  tnode* tempNode = node;
  int temp = 0;
  while(tempNode->parent != NULL){
    //If node is right child
    if(tempNode->parent->right == tempNode){
      //write 1 at bit i
      temp |= (1<<i);
    }
    i++;
    tempNode = tempNode->parent;
  }
  //write to bytesToWrite in reverse order
  for(int n =i-1; n >= 0; n--){
    byte bit = (temp >> n) & 1;
    *byteToWrite |= (bit << (*bitToSet));
    (*bitToSet)--;
    if(*bitToSet < 0){
      //Write byte to file
      fputc(*byteToWrite, out);
      //Reset byteToWrite
      *byteToWrite = 0;
      //Reset bitToSet
      (*bitToSet) = 7;
    }
  }
}

void decodeFile(char* text, tnode* treeRoot){
  FILE* in;
  in = fopen(text, "r");
  FILE* out;
  char fileName[strlen(text) + 5];
  const char* extension = ".dec";
  strcpy(fileName, text);
  strcpy(fileName+strlen(text), extension);
  out = fopen(fileName, "w+");
  if (in == NULL) {
    printf("input file can't be opened \n");
  }
  if (out == NULL) {
    printf("output file can't be opened\n");
  }
  char c = fgetc(in);
  tnode* temp = treeRoot;
  //go through the text file byte by byte until you hit EOF and then return
  //grab a byte and start decoding
  int running = 1;
  while(running) {
    //check if the first bit is a 0 or 1
    //start at treeRoot and make temp pointer to treeRoot
    //go to treeRoot left child if 0, right child if 1
    //go through every bit in the byte
    for(int i = 7; i >= 0; i--) {
      //shifts bit by i
      int bit = (c>>i);
      //clears the byte except the least significant bit
      bit &= 1;
      if(bit == 0) {
	temp = temp->left;
      }else{
	temp = temp->right;
      }
      //when you hit a leafNode, if it's not a termination ch, write the letter to output file
      if(temp->right == NULL && temp->left == NULL) {
	if (temp->c == '\0') {
	  fclose(out);
	  fclose(in);
	  running = 0;
	  return;
	} else {
	  fputc(temp->c, out);
	  //reset temp to treeRoot
	  temp = treeRoot;
	}
      }
    }
    c = fgetc(in);
  }
  fclose(in);
  fclose(out);
}

void printTree(tnode* nodes, int level) {
  if (nodes == NULL) {
  return;
  }
  for (int i = 0; i < level; i++) {
    printf("    ");
  }
  //Some of the chars will mess up the formatting, so this avoids that
  if(nodes->c == ' ') {
    printf("fr: %d, c: sp\n", nodes->frequency);
  } else if(nodes->c == '\n') {
    printf("fr: %d, c: \\n\n", nodes->frequency);
  } else if(nodes->c == '\0') {
    printf("fr: %d, c: \\0\n", nodes->frequency);
  } else {
    printf("fr: %d, c: %c\n", nodes->frequency, nodes->c);
  }
  printTree(nodes->left, level + 1);
  printTree(nodes->right, level + 1);
}
