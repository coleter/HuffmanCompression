#ifndef __HCOMPRESS__
#define __HCOMPRESS__
typedef struct tnode {
   int frequency;
   int c;
   struct tnode* left;
   struct tnode* right;
   struct tnode* parent;
   int isLeaf;
   int side;
}tnode;
typedef unsigned char byte;
tnode* createFreqTable(char* text);
tnode* createHuffmanTree(tnode* nodes);
void encodeFile(char* input, tnode* nodes);
void decodeFile(char* input, tnode* treeRoot);
void encodeCharacter(tnode* node, byte* byteToWrite, int* bitToSet, FILE* out);
void printTree(tnode* node, int level);
#endif
