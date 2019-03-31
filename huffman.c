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
	//char* example = "this this this is is a a a file that that that that that tests a program";
	char* example = "a a a a a dog dog dog dog dog dog dog dog dog cat cat cat cat cat cat cat cat cat cat cat cat button button button button button button button button button button button button button ball ball ball ball ball ball ball ball ball ball ball ball ball ball ball ball and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and and";
	tokenizeString(example);
	buildHeap();
	buildHuffmanTree();
	
	//struct heapNode* min = deleteMin();
	//printf("min %s %d\n", min->item, min->freq);
	//struct heapNode* min2 = deleteMin();
	//printf("min2 %s %d\n", min2->item, min2->freq);
	//buildTree(min, min2);
	
	//insertHeap(newNode);
	/*
	int i = 0;
	for (i = 0; i < heapIndex; i++) {
		printf("item %s: %d\n", minHeap[i]->item, minHeap[i]->freq);
	}
	*/
	//int present = checkIfPresent("file");
	//printf("present %d\n", present);
	return 0;
}
/*
	tokenizes string and puts in token array
*/
void tokenizeString (char* str) {
	int length = strlen(str);
	int i = 0, j = 0;							   
	for (i = 0, j = 0; i < length+1; i++){         
		if (str[i] == '\0' || !isalpha(str[i])){   
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
				limit++;
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
		/*
		//printf("heapindex %d\n", heapIndex);
		struct heapNode * first = deleteMin();
		struct heapNode * second = deleteMin();
		buildTree(first, second);
		//printHeap();
		struct heapNode * third = deleteMin();
		struct heapNode * fourth = deleteMin();
		//printf("third is %s %d fourth is %s %d\n", third->item, third->freq, fourth->item, fourth->freq);
		buildTree(third, fourth);
		//printHeap();
		
		struct heapNode * fifth = deleteMin();
		struct heapNode * sixth = deleteMin();
		buildTree(fifth, sixth);
		//printHeap();
		
		struct heapNode * seventh = deleteMin();
		struct heapNode * eighth = deleteMin();
		buildTree(seventh, eighth);
		printHeap();
		
		struct heapNode * ninth = deleteMin();
		struct heapNode * tenth = deleteMin();
		buildTree(ninth, tenth);
		//printHeap();
		//printHeap();
		*/
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
		printPreorder(minHeap[0]);
	/*
	int i = 0;
	for (i = 0; i < heapIndex; i++) {
		printf("item %s freq %d\n", minHeap[i]->item, minHeap[i]->freq);
	}
	while (minHeap[1] != NULL) {
		printf("heapindex %d", heapIndex);
		struct heapNode* first = deleteMin();
		struct heapNode* second = deleteMin();
		buildTree(first, second);
	}
	*/
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
