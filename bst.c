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
	char* example = "this this this is is a a a file that that that that that tests a program";
	tokenizeString(example);
	buildHeap();
	int i = 0;
	for (i = 0; i < 7; i++) {
		printf("item %s freq %d\n", minHeap[i]->item, minHeap[i]->freq);
	}
	//int present = checkIfPresent("file");
	//printf("present %d\n", present);
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
			int present = checkIfPresent(substr, k);
			if (present == -1) {
				struct heapNode* temp= (struct heapNode*)malloc(sizeof(struct heapNode));
				temp->item = (char*)malloc((length+1)*sizeof(char));
				strcpy(temp->item, substr);
				temp->freq = 1;
				tokens[k] = temp;
				k++;
			} 
			j = i+1;							   
		}
	}
}

int checkIfPresent (char* str, int limit) {
	if (limit == 0) {
		return -1;
	}
	int i = 0;
	for (i = 0; i < limit; i++) {
		if (strcmp(tokens[i]->item, str) == 0) {
			tokens[i]->freq = tokens[i]->freq + 1;
			return i;
		}
	}
	return -1;
}	

void bubbleUp(int index) {
	int parentIndex = (int)(ceil((double)(index-2)/2));
	if (parentIndex < 0) {
		parentIndex = 0;
	}
	printf("the node containing %s %d at %d will be bubbled up and the parent is %d\n", minHeap[index]->item, minHeap[index]->freq, index, parentIndex);
	while (minHeap[parentIndex]->freq > minHeap[index]->freq) {
		struct heapNode* temp = minHeap[parentIndex];
		minHeap[parentIndex] = minHeap[index];
		minHeap[index] = temp;
		index = parentIndex;
		parentIndex = (int)(ceil((double)(index-2)/2));
		if (parentIndex < 0) {
			parentIndex = 0;
		}
	}
}

void buildHeap() {
	int i = 0;
	for (i = 0; i < 7; i++) {
		insertHeap(tokens[i]);
	}
}

void insertHeap(struct heapNode *toBeInserted) {
	//printf("item: %s freq: %d will be inserted at %d\n", toBeInserted->item, toBeInserted->freq, heapIndex);
	minHeap[heapIndex] = toBeInserted;
	if (heapIndex != 0) {
		bubbleUp(heapIndex);
	}
	heapIndex++;
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
