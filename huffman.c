#include "fileCompressor.h"

int main (int argc, char** argv) {
	printf("in huffman\n");
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
	//char* example = "a a a a a dog dog dog dog dog dog dog dog dog cat cat cat cat cat cat cat cat cat cat cat cat button button button button button button button button button button button button button ball ball ball ball ball ball ball ball ball ball ball ball ball ball ball ball and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and";
	//char* example = "a b c d e f a b c d e f a b c d e f a b c d e f a b c d e f b c d e f b c d e f b c d e f b c d e f c d e f c d e f c d e f d e f e f e f e f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f"; 
	tokenizeString(example);
	buildHeap();
	buildHuffmanTree();
	struct huffmanNode* start = head;
	while (start != NULL) {
		printf("%s: ", start->token);
		int i = 0;
		for (i = 0; i < start->limit; i++) {
			printf("%d", start->code[i]);
		}
		printf("\n");
		start = start->next;
	}
	compressString(example);
	return 0;
}
/*
	tokenizes string and puts in token array
*/
void tokenizeString (char* str) {
	int length = strlen(str);
	int i = 0, j = 0;							   
	for (i = 0, j = 0; i < length+1; i++){         
		if (str[i] == '\0' || !isalpha(str[i])){   // !!!!checks non alphanumeric char instead only spaces
			int length = i-j;
			char* substr = malloc(length+1);
			strncpy(substr, str+j, length); 	   
			substr[length] = '\0';
			int present = checkIfPresent(substr);
			if (present == -1) {
				struct heapNode* temp= (struct heapNode*)malloc(sizeof(struct heapNode));
				temp->item = (char*)malloc((length+1)*sizeof(char));
				strcpy(temp->item, substr);
				temp->freq = 1;
				temp->left = NULL;
				temp->right = NULL;
				tokens[limit] = temp;
				limit++;						// make sure tokens[] doesnt seg fault
			} 
			j = i+1;							   
		}
	}
}
/*
	checks if token is already present, and if it is, increases freq
*/
int checkIfPresent (char* str) {
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
/*
	Bubbles inserted heap node
*/
void bubbleUp(int index) {
	//printf("%s: %d will be bubbled up\n", minHeap[index]->item, minHeap[index]->freq);
	int parentIndex = (int)(ceil((double)(index-2)/2));
	if (parentIndex < 0) {
		parentIndex = 0;
	}
	//printf("the node containing %s %d at %d will be bubbled up and the parent is %d\n", minHeap[index]->item, minHeap[index]->freq, index, parentIndex);
	while (minHeap[parentIndex]->freq > minHeap[index]->freq) {
		//printf("node %s: %d will swapped with %s: %d\n", minHeap[index]->item, minHeap[index]->freq, minHeap[parentIndex]->item, minHeap[parentIndex]->freq);
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
/*
	builds heap after token array is done
*/
void buildHeap() {
	int i = 0;
	for (i = 0; i < limit; i++) {
		insertHeap(tokens[i]);
	}
}
/*
	inserts token arrays into heap
*/
void insertHeap(struct heapNode *toBeInserted) {
	//printf("item: %s freq: %d will be inserted at %d\n", toBeInserted->item, toBeInserted->freq, heapIndex);
	minHeap[heapIndex] = toBeInserted;
	if (heapIndex != 0) {
		bubbleUp(heapIndex);
	}
	heapIndex++;
}
/*
	deletes min
*/
struct heapNode* deleteMin() {
	struct heapNode *min = minHeap[0];
	heapIndex--;
	minHeap[0] = minHeap[heapIndex];
	minHeap[heapIndex] = NULL;
	bubbleDown(0);
	return min;
}
/*
	bubble down method for heap
*/
void bubbleDown(int index) {
	//printf("%s: %d will be bubbled down\n", minHeap[index]->item, minHeap[index]->freq);
	int smallest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	if (left < heapIndex && minHeap[left]->freq < minHeap[smallest]->freq) {
		smallest = left;
	}
	if (right < heapIndex && minHeap[right]->freq < minHeap[smallest]->freq) {
		smallest = right;
	}
	if (smallest != index) {
		//printf("node %s: %d will swapped with %s: %d\n", minHeap[index]->item, minHeap[index]->freq, minHeap[smallest]->item, minHeap[smallest]->freq);
		struct heapNode* temp = minHeap[smallest];
		minHeap[smallest] = minHeap[index];
		minHeap[index] = temp;
		bubbleDown(smallest);
	}
}

void buildTree(struct heapNode* node1, struct heapNode* node2) {
	//printf("a node will be built with %s %d and %s %d\n", node1->item, node1->freq, node2->item, node2->freq);
	struct heapNode * newNode = (struct heapNode*)malloc(sizeof(struct heapNode));
	newNode->freq = node1->freq + node2->freq;
	newNode->item = (char*)malloc(6*sizeof(char));
	strcpy(newNode->item, "tree0");
	newNode->left = node1;
	newNode->right = node2;
	insertHeap(newNode);
}

void buildHuffmanTree() {
		
		while (heapIndex != 2) {
			struct heapNode *temp1 = deleteMin();
			struct heapNode *temp2 = deleteMin();
			buildTree(temp1, temp2);
		}
		if (heapIndex == 2) {
			struct heapNode* temp1 = minHeap[0];
			struct heapNode* temp2 = minHeap[1];
			minHeap[0] = NULL;
			minHeap[1] = NULL;
			heapIndex = 0;
			buildTree(temp1, temp2);
		}
		//printHeap();
		//printPreorder(minHeap[0]);
		int arr[100], top = 0;
		compressTree(minHeap[0], arr, top);

}

int isLeaf(struct heapNode * node) {
	if (node->left == NULL && node->right == NULL) {
		return 1;
	}
	return 0;
}

void compressTree (struct heapNode* root, int arr[], int top) {
	if (root->left != NULL) {
		arr[top] = 0;
		compressTree(root->left, arr, top+1);
	}
	if (root->right != NULL) {
		arr[top] = 1;
		compressTree(root->right, arr, top+1);
	}
	if (isLeaf(root) == 1) {
		//printf(" leaf %s: %d\n", root->item, root->freq);
		int* encoding = (int*)malloc(top*sizeof(int));
		int i = 0;
		for (i = 0; i < top; i++) {
			encoding[i] = arr[i];
		}
		struct huffmanNode* temp = (struct huffmanNode*)malloc(sizeof(struct huffmanNode));
		int length = strlen(root->item);
		//printf("%d\n", length);
		temp->token = (char*)malloc((length+1)*sizeof(char));
		strcpy(temp->token, root->item);
		temp->token[length] = '\0';
		temp->code = encoding;
		temp->limit = top;
		struct huffmanNode* start = head;
		if (start == NULL) {
			head = temp;
		} else {
			while (start->next != NULL) {
				start = start->next; 
			}
			start->next = temp;
			//start = start->next;
		}
	}
}

void compressString(char* str) {
	int length = strlen(str);
	int i = 0, j = 0;							   
	for (i = 0, j = 0; i < length+1; i++){         
		if (str[i] == '\0' || !isalpha(str[i])){   // !!!!checks non alphanumeric char instead only spaces
			int length = i-j;
			char* substr = malloc(length+1);
			strncpy(substr, str+j, length); 	   
			substr[length] = '\0';
			printCode(substr);
			j = i+1;							   
		}
	}
	printf("\n");
}

void printCode(char* str) {
	//printf("%s will be compressed ", str);
	
	struct huffmanNode * start = head;
	while (start != NULL) {
		if (strcmp(start->token, str) == 0) {
			int i = 0;
			for (i = 0; i < start->limit; i++) {
				printf("%d", start->code[i]);
			}
		}
		start = start->next;
	}
	//printf("\n");
}

void printHeap() {
	printf("----min heap----\n");
	int i = 0;
	for (i = 0; i < heapIndex; i++) {
			printf("item %s: %d\n", minHeap[i]->item, minHeap[i]->freq);
		}
	printf("----------------\n");
}

void printPreorder(struct heapNode *node) { 
    if (node == NULL) 
          return;
     /* first print data of node */
    printf("%d ", node->freq);   
  	
     /* then recur on left sutree */
    printPreorder(node->left);   
  
     /* now recur on right subtree */
    printPreorder(node->right); 
} 
