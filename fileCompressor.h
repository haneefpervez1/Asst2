#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*
	BST struct
*/
struct BSTnode {
	int key;
	struct BSTnode *left, *right;
};
/*
	Heap node
*/
struct heapNode {
	char* item;
	int freq;
};
struct heapNode* tokens[100];
struct heapNode* minHeap[100];
int heapIndex = 0;
/*
	BST Functions
*/
struct BSTnode *newNode(int);
struct BSTnode * insert (struct BSTnode *, int);
struct BSTnode * search (struct BSTnode *, int);
void inorder(struct BSTnode *);
void tokenizeString(char* str);
int checkIfPresent (char* str, int limit);
void buildHeap();
void bubbleUp(int index);
void insertHeap(struct heapNode *);
struct heapNode* deleteMin();
void bubbleDown();
/*
	fileCompressor functions
*/
void printDirectory();
