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
	tokenizeString(example);
	buildHeap();
	buildHuffmanTree();
	
	//struct heapNode* min = deleteMin();
	//printf("min %s %d\n", min->item, min->freq);
	//struct heapNode* min2 = deleteMin();
	//printf("min2 %s %d\n", min2->item, min2->freq);
	//buildTree(min, min2);
	
	//insertHeap(newNode);
	int i = 0;
	for (i = 0; i < heapIndex; i++) {
		printf("item %s freq %d\n", minHeap[i]->item, minHeap[i]->freq);
	}
	
	//int present = checkIfPresent("file");
	//printf("present %d\n", present);
	return 0;
}
/*
	tokenizes string and puts in token array
*/
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
				temp->left = NULL;
				temp->right = NULL;
				tokens[k] = temp;
				k++;
			} 
			j = i+1;							   
		}
	}
}
/*
	checks if token is already present, and if it is, increases freq
*/
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
/*
	Bubbles inserted heap node
*/
void bubbleUp(int index) {
	int parentIndex = (int)(ceil((double)(index-2)/2));
	if (parentIndex < 0) {
		parentIndex = 0;
	}
	//printf("the node containing %s %d at %d will be bubbled up and the parent is %d\n", minHeap[index]->item, minHeap[index]->freq, index, parentIndex);
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
/*
	builds heap after token array is done
*/
void buildHeap() {
	int i = 0;
	for (i = 0; i < 7; i++) {
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
	bubbleDown();
	return min;
}
/*
	bubble down method for heap
*/
void bubbleDown() {
	//printf("node containing %s %d will be removed\n", minHeap[0]->item, minHeap[0]->freq);
	heapIndex--;
	minHeap[0] = minHeap[heapIndex];
	minHeap[heapIndex] = NULL;
	int left = 1; int right = 2; int parent = 0;
	/*
		might segfault if tree is unbalanced, havent tested yet
	*/
	printf("-------bubble down-------\n");
	printf("heapIndex %d\n", heapIndex);
	int i = 0;
	for (i = 0; i < heapIndex; i++) {
		printf("item %s freq %d\n", minHeap[i]->item, minHeap[i]->freq);
	}
	while (minHeap[parent]->freq > minHeap[left]->freq || minHeap[parent]->freq > minHeap[right]->freq) {
		//printf("comparing %s %d with %s %d and %s %d\n", minHeap[parent]->item, minHeap[parent]->freq, minHeap[left]->item, minHeap[left]->freq, minHeap[right]->item, minHeap[right]->freq);
		if (minHeap[left]->freq <= minHeap[right]->freq) {
			struct heapNode* temp = minHeap[left];
			minHeap[left] = minHeap[parent];
			minHeap[parent] = temp;
			parent = left;
			//printf("bubbledown left\n");
			//printf("parent before segfault %d\n", parent);
			left = 2*parent+1;
			right = 2*parent+2;
			if (right >= heapIndex || left >= heapIndex) {
				//printf("right %d\n", right);
				return;
			}
			//printf("parent %d left %d right %d heap Index %d\n", parent, left, right, heapIndex);
		} else if (minHeap[left]->freq > minHeap[right]->freq) {
			struct heapNode* temp = minHeap[right];
			minHeap[right] = minHeap[parent];
			minHeap[parent] = temp;
			parent = right;
			//printf("bubbledown right\n");
			if (parent <= heapIndex) {
				//printf("parent %d\n", parent);
				return;
			}
			left = 2*parent+1;
			right = 2*parent+2;
			if (right >= heapIndex || left >= heapIndex) {
				//printf("parent %d\n", parent);
				return;
			}
			//printf("parent %d left %d right %d\n", parent, left, right);
		}
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
		
		//printf("heapindex %d\n", heapIndex);
		struct heapNode * first = deleteMin();
		struct heapNode * second = deleteMin();
		buildTree(first, second);
	
		struct heapNode * third = deleteMin();
		struct heapNode * fourth = deleteMin();
		//printf("third is %s %d fourth is %s %d\n", third->item, third->freq, fourth->item, fourth->freq);
		
		buildTree(third, fourth);
		
		struct heapNode * fifth = deleteMin();
		struct heapNode * sixth = deleteMin();
		buildTree(fifth, sixth);
	int i = 0;
	for (i = 0; i < heapIndex; i++) {
		printf("item %s freq %d\n", minHeap[i]->item, minHeap[i]->freq);
	}
	/*
		This part causes the segfault - in bubble down, one of the children is null
	*/
		struct heapNode * seventh = deleteMin();
		struct heapNode * eighth = deleteMin();
		buildTree(seventh, eighth);
		/*
		struct heapNode * ninth = deleteMin();
		struct heapNode * tenth = deleteMin();
		buildTree(ninth, tenth);
		*/
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


