#include "fileCompressor.h"

int main (int argc, char** argv) {
	printf("in bst\n");
	/*
	FILE *fptr;
	fptr = fopen(argv[1], "r");
	char c;
	int numWords = 0;
	while(!feof(fptr)) {
		fscanf(fptr, "%c", &c);
		if (c == ' ') {
			numWords++;
		}
	}
	printf("There are %d words in this file.\n", numWords+1);
	fclose(fptr);
	*/
	char* example = "this is file that tests a program";
	tokenizeString(example);
	int present = checkIfPresent("this");
	printf("present %d\n", present);
	return 0;
}

void tokenizeString (char* str) {
	int length = strlen(str);
	int i = 0, j = 0, k = 0;							   
	for (i = 0, j = 0; i < length+1; i++){         
		if (str[i] == '\0' || !isalpha(str[i])){   
			int length = i-j;
			char* substr = malloc(length+1);
			strncpy(substr, str+j, length); 	   
			substr[length] = '\0';
			//int present = checkIfPresent(substr);
			//if (present == 0) {
				struct heapNode* temp= (struct heapNode*)malloc(sizeof(struct heapNode));
				temp->item = (char*)malloc((length+1)*sizeof(char));
				strcpy(temp->item, substr);
				temp->freq = 1;
				printf("item: %s\nfreq: %d\n", temp->item, temp->freq);
				minHeap[k] = temp;
				k++;
			//}
			j = i+1;							   
		}
	}
}

int checkIfPresent (char* str) {
	int i = 0;
	for (i = 0; i < 7; i++) {
		if (strcmp(minHeap[i]->item, str) == 0) {
			int temp = minHeap[i]->freq;
			minHeap[i]->freq = temp+1;
			return 1;
		}
	}
	return 0;
}	

struct BSTnode *newNode(int key) {
	struct BSTnode *temp = (struct BSTnode *)malloc(sizeof(struct BSTnode));
	temp->key = key;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

struct BSTnode * insert (struct BSTnode *node, int key) {
	if (node == NULL){
		return newNode(key);
	}
	if (key < node->key) {
		node->left = insert(node->left, key);
	} else if (key > node->key) {
		node->right = insert(node->right, key);
	}
	return node;
}

struct BSTnode * search (struct BSTnode *root, int key) {
	if (root == NULL || root->key == key) {
		return root;
	}
	if (root->key < key) {
		return search(root->right, key);
	}
	return search(root->left, key);
}

void inorder(struct BSTnode *root) 
{ 
    if (root != NULL) 
    { 
        inorder(root->left); 
        printf("%d \n", root->key); 
        inorder(root->right); 
    } 
} 
