#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

/*
	BST struct
*/
struct node {
	int key;
	struct node *left, *right;
};
/*
	BST Functions
*/
struct node *newNode(int);
struct node * insert (struct node *, int);
struct node * search (struct node *, int);
void inorder(struct node *);
/*
	fileCompressor functions
*/
void printDirectory();
