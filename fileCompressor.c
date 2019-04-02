#include "fileCompressor.h"
/*
int main (int argc, char** argv) {
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
	fopen(fptr);
	char** strings[numWords][100];
	while(!feof(fptr)){
		fscanf(fptr, "%s", 
	}
	return 0;
}
*/
void buildCB(char * file, int fd)
{
 int i=1;
 char buff[1];
 int x = read(fd, buff, 1);
 char string[10000];
 string[0]=buff[0]; 
 	while(x!=0)
 	{
 	 x = read(fd, buff, 1);
 	 if(buff[0]!='\n')
 	 {
 	 string[i]=buff[0];
 	 }
 	 i++;
 	 //printf("%c", buff[0]);
 	}
 /*for(i=0;i<strlen(string);i++)
 {
  printf("%c", string[i]);
 }*/
 tokenizeString(string);
 /*for(i=0;i<limit;i++)
 {
  printf("%s", tokens[i]->item);
 }*/
}
void compress(char * file, int fd, char* codebook)
{
  
}
void decompress(char* file, int fd, char* codebook)
{
 
}
void printDirectory() {
	/*
		Prints out files in current directory
	*/
	struct dirent *de;
	
	DIR *dr = opendir("./");
	
	if (dr == NULL) {
		printf("error\n");
	}
	while ((de = readdir(dr)) != NULL) {
		printf("%s\n", de->d_name);
	}
	closedir(dr);
}
void Recursive(char * flag, char * path, char * codebook, int cont) {
	int index=0;
	int i;
	int check=0;
	struct dirent *de;
	
	DIR * dr = opendir(path);

	
	if (dr == NULL) {
		printf("error\n");
		return;
	}
	while ((de = readdir(dr)) != NULL) {
		if( de->d_type == DT_DIR)
		{
		 if( (strcmp(de->d_name, ".") == 0) || (strcmp(de->d_name, "..") == 0))
		 {
		  continue;
		 }
		 printf("%s\n", de->d_name);
		 char * temp = (char*) malloc(sizeof(path) + sizeof(de -> d_name) + 2);
		 strcpy(temp, path);
		 strcat(temp, "/");
		 strcat(temp, de->d_name);
		 //printf("%s\n", temp);
		 Recursive(flag, temp, codebook, index++);
		}
		else
		{
		 char * temp = (char*) malloc(sizeof(path) + sizeof(de -> d_name) + 2);
		 strcpy(temp, path);
		 strcat(temp, "/");
		 strcat(temp, de->d_name);
		 //printf("%s\n", de->d_name);
		 int fd;
		 	switch(flag[1])
 				{
 		 		case('b'):
 	 			fd = open(temp, O_RDONLY | O_CREAT);
 	 			buildCB(temp, fd);
 	 			close(fd); 
 	 			check=1;
 				// printf("%d", fd);
 				break;
 	 			case('c'):
 	 			 fd = open(temp, O_RDONLY | O_CREAT); 
 	 			 compress(temp, fd, codebook);
 	 			 close(fd);
 	 			 break;
 	 			case('d'):
 	 			 //decompress(file, fd, codebook);
 	 			 break;
				}
		}
	}
	closedir(dr);
	if (check==1 && index==0)
	{
	for(i=0;i<limit;i++)
 	{
  	printf("%s\n", tokens[i]->item);
 	}
	 buildHeap();
 	 buildHuffmanTree();
 	 buildCodeBook();
	}
	if (check==2 && index==0)
	{
	for(i=0;i<limit;i++)
 	{
  	printf("%s\n", tokens[i]->item);
 	}
	 buildHeap();
 	 buildHuffmanTree();
 	 buildCodeBook();
	}
}
int main (int argc, char ** argv)
{
 int fd;
 char* flag2;
 char* flag = argv[1];
 char* file = argv[2];
 char* codebook = argv[3];
 //printf("%s %s %s", flag, file, codebook);
 //printDirectory();
 	switch(flag[1])
 	{
 	 case('b'):
 	  fd = open(file, O_RDONLY | O_CREAT);
 	  buildCB(file, fd);
 	  buildHeap();
 	  buildHuffmanTree();
 	  buildCodeBook();
 	  close(fd);
 	 // printf("%d", fd);
 	  break;
 	 case('c'):
 	  fd = open(file, O_RDONLY | O_CREAT); 
 	  compress(file, fd, codebook);
 	  break;
 	 case('d'):
 	  //decompress(file, fd, codebook);
 	  break;
 	 case('R'):
 	  flag2 = argv[2];
 	  file = argv[3];
 	  if(flag2==NULL)
 	  {
 	  return 0;
	  }
 	  codebook = argv[4];
 	  Recursive(flag2, file, codebook, 0);
 	 break;
 	}
  return 0;
}
/*
	tokenizes string and puts in token array
*/
void tokenizeString (char* str) {
	int length = strlen(str);
	int i = 0, j = 0;							   
	for (i = 0, j = 0; i < length+1; i++){         
		if (str[i] == '\0' || str[i] == ' '){   // !!!!checks non alphanumeric char instead only spaces
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
			while (str[i] == ' ') {
				i++;
			}
			j = i;							   
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

void buildCodeBook() {
	printf("this will build the codebook\n");
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
 	int CB = creat("HuffmanCodeBook", mode);
 	//write(CB, "working", strlen("working"));
	write(CB, "/\n", strlen("/\n"));
	struct huffmanNode *ptr = head;
	while (ptr != NULL) {
		int i = 0;
		for (i = 0; i < ptr->limit; i++) {
			char* c = "a";
			if (ptr->code[i] == 0) {
				c = "0";
			} else if (ptr->code[i] == 1) {
				c = "1";
			}
			write(CB, c, strlen(c));
		}
		write(CB, " ", strlen(" "));
		write(CB, ptr->token, strlen(ptr->token));
		write(CB, "\n", strlen("\n"));
		ptr = ptr->next;
	}
	write(CB, "\n", strlen("\n"));
}

void compressString(char* str) {
	int length = strlen(str);
	int i = 0, j = 0;							   
	for (i = 0, j = 0; i < length+1; i++){         
		if (str[i] == '\0' || str[i] == ' '){   // !!!!checks non alphanumeric char instead only spaces
			int length = i-j;
			char* substr = malloc(length+1);
			strncpy(substr, str+j, length); 	   
			substr[length] = '\0';
			printCode(substr);
			while (str[i] == ' ') {
				i++;
			}
			j = i;							   
		}
	}
	printf("\n");
}

void decompressString(struct huffmanNode* codeBook, char* str) {
	/*
		Read in shit from code book to huffNode ll and get token and code - still need to implement
		readShit();
	*/
	struct heapNode *root = (struct heapNode*)malloc(sizeof(struct heapNode));
	root->item = "tree";
	root->freq = 0;
	root->left = NULL;
	root->right = NULL;
	struct huffmanNode* ptr = codeBook;
	while (ptr != NULL) {
		int i = 0;
		struct heapNode* first = root;
		for (i = 0; i < ptr->limit; i++) {
			//printf("%d ", ptr->code[i]);
			if (ptr->code[i] == 0) {
				//printf("go left\n");
				struct heapNode *temp = (struct heapNode*)malloc(sizeof(struct heapNode));
				if (i+1 == ptr->limit) {
					//printf("inserting %s\n", ptr->token);
					int length = strlen(ptr->token);
					temp->item = (char*)malloc((length+1)*sizeof(char));
					strcpy(temp->item, ptr->token);
					temp->freq = 0;
				} else {
				//	printf("inserting tree\n");
					temp->item = (char*)malloc(5*sizeof(char));
					//strcpy(temp->item, "left");
					temp->freq = 0;
				}
				//temp->left = NULL;
				//temp->right = NULL;
				//printf("inserting %s\n");
				if (first->left == NULL) {
					first->left = temp;
				}
				first = first->left;
			} if (ptr->code[i] == 1) {
				//printf("go right\n");
				struct heapNode *temp = (struct heapNode*)malloc(sizeof(struct heapNode));
				if (i+1 == ptr->limit) {
				//	printf("inserting %s\n", ptr->token);
					int length = strlen(ptr->token);
					temp->item = (char*)malloc((length+1)*sizeof(char));
					strcpy(temp->item, ptr->token);
					temp->freq = 0;
				} else {
					//printf("inserting placeholder\n");
					temp->item = (char*)malloc(6*sizeof(char));
					strcpy(temp->item, "right");
					temp->freq = 0;
				}
				//temp->left = NULL;
				//temp->right = NULL;
				//printf("inserting %s\n", );
				if (first->right == NULL) {
					first->right = temp;
				}
				first = first->right;
			}
		}
		//printf("------\n");
		ptr = ptr->next;
	}
	//printPreorder(root);
	//printf("\nstr %s\n", str);
	int length = strlen(str);
	struct heapNode *first = root;
	//printPreorder(first);
	//printf("\n");
	int i = 0;
	for (i = 0; i < length; i++) {
		if (str[i] == '0') {
			first = first->left;
		}
		if (str[i] == '1') {
			first = first->right;
		}
		if (isLeaf(first) == 1) {
			printf("%s ", first->item);
			first = root;
		}
	}
	printf("\n");
	/*
	while (ptr != NULL) {
		
		ptr = ptr->next;
	}
	*/
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
    printf("%s ", node->item);   
  	
     /* then recur on left sutree */
    printPreorder(node->left);   
  
     /* now recur on right subtree */
    printPreorder(node->right); 
}
struct huffmanNode* readCodeBook(char* file) {
int fd1 = open(file, O_RDONLY);
char* example = (char*)malloc(2*sizeof(char));
int f = read(fd1, example, 2);
//int* codes = (int*)malloc(sizeof(int));
//printf("first time\n");
int codeCounter = 0;
int stringCounter = 0;
struct huffmanNode* root = NULL;
while (f != 0) {
f = read(fd1, example, 1);
if (example[0] == '0' || example[0] == '1') {
codeCounter++;
}
if (example[0] == '\t') {
//printf("codecounter %d\n", codeCounter);
struct huffmanNode* temp = (struct huffmanNode*)malloc(sizeof(struct
huffmanNode));
temp->limit = codeCounter;
temp->code = (int*)malloc(codeCounter*sizeof(int));
//printf("%d has been malloced\n",codeCounter);
temp->token = NULL;
if (root == NULL) {
root = temp;
} else {
temp->next = root;
root = temp;

}
codeCounter = 0;
}
if (isalpha(example[0])) {
stringCounter++;
}
if (example[0] == '\n') {
if (stringCounter != 0) {
root->token = (char*)malloc((stringCounter+1)*sizeof(char));
root->token[stringCounter] = '\0';
//printf("%d can be insertred\n", stringCounter);
//strcpy(ptr->token, "s");
stringCounter = 0;
}
//printf("string counter %d\n", stringCounter);
}
//printf("%s", example);
}
reverse(&root);
struct huffmanNode* ptr = root;
/*
while (ptr != NULL) {
printf("root is %s %d\n", ptr->token, ptr->limit);
ptr = ptr->next;
}
*/
close(fd1);
ptr = root;
int fd2 = open(file, O_RDONLY);
int p = read(fd2, example, 2);
//printf("second\n");
while (p != 0) {
p = read(fd2, example, 1);
if (example[0] == '0' || example[0] == '1') {
int digit = 0;
if (example[0] == '1') {
digit = 1;
}
ptr->code[codeCounter] = digit;
codeCounter++;
}
if (example[0] == '\t') {
/*
printf("this is the code array\n");
int i = 0;
for (i = 0; i < ptr->limit; i++) {
printf("%d", ptr->code[i]);
}
*/
//ptr = ptr->next;
codeCounter = 0;
}
if (isalpha(example[0])) {
ptr->token[stringCounter] = example[0];
stringCounter++;
}
if (example[0] == '\n') {
if (stringCounter != 0) {
//printf("string counter %d\n", stringCounter);
//ptr->token[stringCounter] = '\0';
//printf("%s has been inserted\n", ptr->token);
/*
struct huffmanNode* start = root;
while (start != NULL) {
printf("%s: ", start->token);
int i = 0;
for (i = 0; i < start->limit; i++) {
printf("%d", start->code[i]);
}
printf("\n");
start = start->next;
}
*/
/*
if (ptr->next == NULL) {
printf("%s last thing\n", ptr->token);
}
*/
ptr = ptr->next;
stringCounter = 0;
}
}
//printf("%s", example);
}
/*
struct huffmanNode* start = root;
while (start != NULL) {
printf("%s: ", start->token);
int i = 0;
for (i = 0; i < start->limit; i++) {
printf("%d", start->code[i]);
}
printf("\n");
start = start->next;
}
*/
return root;
}

void reverse(struct huffmanNode** head_ref) {
    struct huffmanNode* prev   = NULL;
    struct huffmanNode* current = *head_ref;
    struct huffmanNode* next = NULL;
    while (current != NULL)
    {
        // Store next
        next  = current->next;

        // Reverse current node's pointer
        current->next = prev;

        // Move pointers one position ahead.
        prev = current;
        current = next;
    }
    *head_ref = prev;
}
