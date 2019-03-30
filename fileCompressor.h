#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

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
struct heapNode* minHeap[100];
/*
	BST Functions
*/
struct BSTnode *newNode(int);
struct BSTnode * insert (struct BSTnode *, int);
struct BSTnode * search (struct BSTnode *, int);
void inorder(struct BSTnode *);
void tokenizeString(char* str);
int checkIfPresent (char* str, int limit);
/*
	fileCompressor functions
*/
void printDirectory();
