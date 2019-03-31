#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*
	BST struct

struct BSTnode {
	struct heapNode* item;
	struct BSTnode *left, *right;
};
*/
/*
	Heap node
*/
struct heapNode {
	char* item;
	int freq;
	struct heapNode *left, *right;
};
struct heapNode* tokens[100];
struct heapNode* minHeap[100];
int heapIndex = 0;
int limit = 0;
/*
	BST Functions
*/
//void inorder(struct BSTnode *);
void tokenizeString(char* str);
int checkIfPresent (char* str);
void buildHeap();
void bubbleUp(int index);
void insertHeap(struct heapNode *);
struct heapNode* deleteMin();
void bubbleDown();
void buildTree(struct heapNode*, struct heapNode*);
void buildHuffmanTree();
void printPreorder(struct heapNode *node);
void printHeap();
/*
	fileCompressor functions
*/
void printDirectory();
void buildCB( char * file);
void compress( char * file);
void decompress( char * file);



