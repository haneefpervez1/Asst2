#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>

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
/*
	struct to store huffman encoding
*/
struct huffmanNode {
	char* token;
	int* code;
	int limit;
	struct huffmanNode *next;
};
struct huffmanNode * head;
struct heapNode* tokens[1000];
struct heapNode* minHeap[1000];
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
int isLeaf(struct heapNode *);
void compressTree (struct heapNode*, int [], int);
void buildCodeBook();
void compressString(char*);
void decompressString(struct huffmanNode* , char* );
void printCode(char*);
void printPreorder(struct heapNode *node);
void printHeap();
/*
	fileCompressor functions
*/
void printDirectory();
void buildCB( char * file, int fd);
void compress( char * file, int fd, char* codebook);
void decompress( char * file, int fd, char* codebook);



