#include "fileCompressor.h"
/*
	Builds a codebook for a file
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
	 	}
	tokenizeString(string);
}
/*
	Compresses a file
*/
void compress(char * file, int fd, char* codebook)
{
	int i=0;
	char buff[1];
	int x = read(fd, buff, 1);
	char string[10000];
	while(x!=0)
  	{
  		if(buff[0]!='\n')
  		{
  		string[i] = buff[0];
  		i++;
  		}
  	x = read(fd, buff, 1);
  }
	struct huffmanNode* codes = readCodeBook(codebook);
	compressString(string, codes, file);
}
/*
	Decompresses a file
*/
void decompress(char* file, int fd, char* codebook)
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
	}
	struct huffmanNode* codes = readCodeBook(codebook);
	decompressString(codes, string, file);
}
/*
	Prints a directory
*/
void printDirectory() {
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
/*
	Recursively goes file path
*/
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
		 int fd;
		 	switch(flag[1])
 				{
 		 		case('b'):
 				if (codebook !=NULL)
 				  {
 				   printf("Error. Huffman Codebook already provided.");
 				   return;
 				  }
 	 			fd = open(temp, O_RDONLY | O_CREAT);
 	 			buildCB(temp, fd);
 	 			close(fd); 
 	 			check=1;
 				break;
 	 			case('c'):
 			  	if(de->d_type!=DT_REG)
			  	{
	  				printf("Error. Only compress regular files");
	  				return;
	  			}
	  			if(codebook==NULL)
				  {
				  	printf("Error. No codebook given");
				  }
 	 			 fd = open(temp, O_RDONLY | O_CREAT); 
 	 			 compress(temp, fd, codebook);
 	 			 close(fd);
 	 			 check=2;
 	 			 break;
 	 			case('d'):
 	 			 if(strstr(temp, ".hcz") ==NULL)
				 {
				  	printf("Error. Only decompress regular files with type .hcz extension");
			 	  	return;
				 }
				 if(codebook==NULL)
				  {
				  	printf("Error. No codebook given");
				  }
 	 			 fd = open(temp, O_RDONLY | O_CREAT);
 	 			 decompress(temp, fd, codebook);
 	 			 close(fd);
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
}
int main (int argc, char ** argv)
{
 if(argc>5)
 {
  printf("Error. Too mnay input argumetns");
  return 0;
 }
 if(argc<3)
 {
  printf("Error: Too few inputs");
  return 0;
 }
 int fd;
 char* flag2;
 char* flag = argv[1];
 char* file = argv[2];
 char* codebook = argv[3];
 struct dirent *de;
 DIR * dr = opendir(".");
 	switch(flag[1])
 	{
 	 case('b'):
 	 if (argv[3] !=NULL)
 	  {
 	   printf("Error. Huffman Codebook already provided.");
 	   return 0;
 	  }
 	  fd = open(file, O_RDONLY | O_CREAT);
 	  buildCB(file, fd);
 	  buildHeap();
 	  buildHuffmanTree();
 	  buildCodeBook();
 	  close(fd);
 	 // printf("%d", fd);
 	  break;
 	 case('c'):
 	  if(dr!=NULL)
 	  {
 	  de = readdir(dr);
 	  	if(de->d_type!=DT_REG)
	  	{
	  		printf("Error. Only compress regular files");
	  		return 0;
	  	}
 	  }
 	  if(codebook==NULL)
	  {
	  	printf("Error. No codebook given");
	  	return 0;
	  }
 	  fd = open(file, O_RDONLY | O_CREAT); 
 	  compress(file, fd, codebook);
 	  close(fd);
 	  break;
 	 case('d'):
 	  if(strstr(file, ".hcz") ==NULL)
 	  {
 	  	printf("Error. Only decompress regular files with type .hcz extension");
 	  	return 0;
	  }
	  if(codebook==NULL)
	  {
	  	printf("Error. No codebook given");
	  	return 0;
	  }
 	  fd = open(file, O_RDONLY | O_CREAT);
    	  decompress(file, fd, codebook);
    	  close(fd);
 	  break;
 	 case('R'):
 	  flag2 = argv[2];
 	  file = argv[3];
 	  if(flag2[1] != 'b' || flag2[1] != 'c' || flag2[1] != 'd' )
 	  {
 	  	printf("Error. No flag of either -c, -b, or -d indicated");
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
		if (str[i] == '\0' || str[i] == ' '){   
		int length = i-j;
		char* substr = malloc(length+1);
		strncpy(substr, str+j, length);
		substr[length] = '\0';
		int present = checkIfPresent(substr); // adds tokens to token array
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
			while (str[i] == ' ') {			// adds space to token array
				char* temp1 = "$s";
				int check = checkIfPresent(temp1);
				if (check == -1) {
					struct heapNode* temp= (struct heapNode*)malloc(sizeof(struct heapNode));
					temp->item = (char*)malloc((3)*sizeof(char));
					strcpy(temp->item, temp1);
					temp->freq = 1;
					temp->left = NULL;
					temp->right = NULL;
					tokens[limit] = temp;
					limit++;
				}
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
			tokens[i]->freq = tokens[i]->freq + 1;		// increases freq
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
	while (minHeap[parentIndex]->freq > minHeap[index]->freq) {
		struct heapNode* temp = minHeap[parentIndex];		//swaps with parent
		minHeap[parentIndex] = minHeap[index];
		minHeap[index] = temp;								
		index = parentIndex;
		parentIndex = (int)(ceil((double)(index-2)/2));		// getting parent index
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
		insertHeap(tokens[i]);			// insert tokens one by one
	}
}
/*
	inserts token arrays into heap
*/
void insertHeap(struct heapNode *toBeInserted) {
	//printf("item: %s freq: %d will be inserted at %d\n", toBeInserted->item, toBeInserted->freq, heapIndex);
	minHeap[heapIndex] = toBeInserted;
	if (heapIndex != 0) {			// bubble up after insertion
		bubbleUp(heapIndex);
	}
	heapIndex++;
}
/*
	deletes min from heap
*/
struct heapNode* deleteMin() {
	struct heapNode *min = minHeap[0];
	heapIndex--;
	minHeap[0] = minHeap[heapIndex];	// swap first and last node
	minHeap[heapIndex] = NULL;
	bubbleDown(0);				// bubble down after deletion
	return min;
}
/*
	bubble down method for heap
*/
void bubbleDown(int index) {
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
		struct heapNode* temp = minHeap[smallest];
		minHeap[smallest] = minHeap[index];
		minHeap[index] = temp;
		bubbleDown(smallest);
	}
}
/*
	Builds a tree out of two nodes from the min heap, node1 and node2 may also be trees
*/
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
/*
	makes the final huffman tree
*/
void buildHuffmanTree() {
		
		while (heapIndex != 2) {
			struct heapNode *temp1 = deleteMin();
			struct heapNode *temp2 = deleteMin();
			buildTree(temp1, temp2);
		}
		if (heapIndex == 2) {						// reduces all nodes to one tree
			struct heapNode* temp1 = minHeap[0];
			struct heapNode* temp2 = minHeap[1];
			minHeap[0] = NULL;
			minHeap[1] = NULL;
			heapIndex = 0;
			buildTree(temp1, temp2);
		}
		int arr[100], top = 0;
		compressTree(minHeap[0], arr, top);

}
/*
	Checks if given node is leaf node
*/
int isLeaf(struct heapNode * node) {
	if (node->left == NULL && node->right == NULL) {
		return 1;
	}
	return 0;
}
/*
	Makes a linked list that holds all the tokens and the corressponding encoding
*/
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
		for (i = 0; i < top; i++) {						// making code []
			encoding[i] = arr[i];
		}
		struct huffmanNode* temp = (struct huffmanNode*)malloc(sizeof(struct huffmanNode));
		int length = strlen(root->item);
		//printf("%d\n", length);
		temp->token = (char*)malloc((length+1)*sizeof(char));		// adding to LL for tokens and encodings
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
		}
	}
}
/*
	Creates a HuffmanCodebook file and puts the encodings and tokens with the proper formatting
*/
void buildCodeBook() {
	//printf("this will build the codebook\n");
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
 	int CB = creat("HuffmanCodebook", mode);			// creating file
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
		write(CB, "\t", strlen("\t"));
		write(CB, ptr->token, strlen(ptr->token));
		write(CB, "\n", strlen("\n"));
		ptr = ptr->next;
	}
	write(CB, "\n", strlen("\n"));
}
/*
	Takes a file and changes the string inside to the huffman encoding
*/
void compressString(char* str, struct huffmanNode * ptr, char* file) {
	strcat(file, ".hcz");		// creating file name
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int result = creat(file, mode);
	//printf("result%d\n", result);
	int length = strlen(str);
	//char* initial = "";
	int i = 0, j = 0;
	for (i = 0, j = 0; i < length+1; i++){
		if (str[i] == '\0' || str[i] == ' '){
			int length = i-j;
			char* substr = malloc(length+1);
			strncpy(substr, str+j, length);
			substr[length] = '\0';
			char* tempString = (char*)malloc(5*sizeof(char));
			tempString = printCode(substr, ptr);				// this function gets the code for the token
			write(result, tempString, strlen(tempString));
			while (str[i] == ' ') {							// to deal with spaces
				char* temporaryString = printCode("$s", ptr);
				write(result, temporaryString, strlen(temporaryString));
				i++;
			}
			j = i;
		}
	}
}
/*
	This function takes a HuffmanCodebook file and builds the corresponding huffman tree
*/
void decompressString(struct huffmanNode* codeBook, char* str, char * file) {
	struct heapNode *root = (struct heapNode*)malloc(sizeof(struct heapNode));	// this will be the tree made from codebook
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
			if (ptr->code[i] == 0) {	// going left and building node, if not leaf node, just make placeholder for traversal
				//printf("go left\n");
				struct heapNode *temp = (struct heapNode*)malloc(sizeof(struct heapNode));
				if (i+1 == ptr->limit) {
					//printf("inserting %s\n", ptr->token);
					int length = strlen(ptr->token);
					temp->item = (char*)malloc((length+1)*sizeof(char));
					strcpy(temp->item, ptr->token);
					temp->freq = 0;
				} else {
					temp->item = (char*)malloc(5*sizeof(char));
					temp->freq = 0;
				}
				if (first->left == NULL) {
					first->left = temp;
				}
				first = first->left;
			} if (ptr->code[i] == 1) { 	/// going left and building node, if not leaf node, just make placeholder for traversal
				struct heapNode *temp = (struct heapNode*)malloc(sizeof(struct heapNode));
				if (i+1 == ptr->limit) {
					int length = strlen(ptr->token);
					temp->item = (char*)malloc((length+1)*sizeof(char));
					strcpy(temp->item, ptr->token);
					temp->freq = 0;
				} else {
					temp->item = (char*)malloc(6*sizeof(char));
					strcpy(temp->item, "right");
					temp->freq = 0;
				}
				if (first->right == NULL) {
					first->right = temp;
				}
				first = first->right;
			}
		}
	ptr = ptr->next;
	}
	int length = strlen(str);
	struct heapNode *first = root;
	//printf("file %s\n", file);
	int resultLength = ((int)strlen(file)) - 4;
	//printf("result length %d\n", resultLength);
	char * resultFile = (char*)malloc(resultLength*sizeof(char));
	strncpy(resultFile, file, resultLength);
	//printf("resultFile %s \n", resultFile);
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int result = creat(resultFile, mode);
	int i = 0;
	// traversing tree
	for (i = 0; i < length; i++) {
		if (str[i] == '0') {
			first = first->left;
		}
		if (str[i] == '1') {
			first = first->right;
		}
		if (isLeaf(first) == 1) {
		if (strcmp(first->item, "$s") == 0) {		// if node is leaf node print token
			write(result, " ", strlen(" "));
		} else {
			write(result, first->item, strlen(first->item));
		}
		first = root;
		}
	}

}
/*
	Returns the encoding for a token
*/
char* printCode(char* str, struct huffmanNode * ptr) {
	struct huffmanNode * start = ptr;
	while (start != NULL) {
		if (strcmp(start->token, str) == 0) {
			char * result = (char*)malloc((start->limit+1) * sizeof(char));
			int i = 0;
			for (i = 0; i < start->limit; i++) {
				char c;
				if (start->code[i] == 0) {
				c = '0';
				} else if (start->code[i] == 1) {
				c = '1';
				}
				result[i] = c;
			}
			result[start->limit] = '\0';
			return result;
		}
		start = start->next;
	}
	return NULL;
}
/*
	Reads a HuffmanCodebook file and fills the LL that holds the token and encodings
*/
struct huffmanNode* readCodeBook(char* file) {
	int fd1 = open(file, O_RDONLY);
	char* example = (char*)malloc(2*sizeof(char));
	int f = read(fd1, example, 2);
	int codeCounter = 0;
	int stringCounter = 0;
	struct huffmanNode* root = NULL;
	while (f != 0) {
		f = read(fd1, example, 1);
		if (example[0] == '0' || example[0] == '1') {
			codeCounter++;
		}
		if (example[0] == '\t') {
			struct huffmanNode* temp = (struct huffmanNode*)malloc(sizeof(struct
			huffmanNode));
			temp->limit = codeCounter;
			temp->code = (int*)malloc(codeCounter*sizeof(int));
			temp->token = NULL;
			if (root == NULL) {
				root = temp;
			} else {
				temp->next = root;
				root = temp;

			}
			codeCounter = 0;
		}
		if (example[0] != '0' && example[0] != '1' && example[0] != '\t' && example[0] != '\n') {
			stringCounter++;
		}
		if (example[0] == '\n') {
			if (stringCounter != 0) {
				root->token = (char*)malloc((stringCounter+1)*sizeof(char));
				root->token[stringCounter] = '\0';
				stringCounter = 0;
			}
		}
	}
	reverse(&root);
	struct huffmanNode* ptr = root;
	close(fd1);
	ptr = root;
	int fd2 = open(file, O_RDONLY);
	int p = read(fd2, example, 2);
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
			codeCounter = 0;
		}
		if (example[0] != '0' && example[0] != '1' && example[0] != '\t' &&
			example[0] != '\n') {
			ptr->token[stringCounter] = example[0];
			stringCounter++;
		}
		if (example[0] == '\n') {
			if (stringCounter != 0) {
				ptr = ptr->next;
				stringCounter = 0;
			}
		}
	}

	return root;
}
/*
	prints the heap
*/
void printHeap() {
	printf("----min heap----\n");
	int i = 0;
	for (i = 0; i < heapIndex; i++) {
			printf("item %s: %d\n", minHeap[i]->item, minHeap[i]->freq);
		}
	printf("----------------\n");
}
/*
	prints a tree using preorder traversal
*/
void printPreorder(struct heapNode *node) { 
    if (node == NULL) 
          return;
    printf("%s ", node->item);   
    printPreorder(node->left);   
    printPreorder(node->right); 
}
/*
	Reverses a LL
*/
void reverse(struct huffmanNode** head_ref) {
    struct huffmanNode* prev   = NULL;
    struct huffmanNode* current = *head_ref;
    struct huffmanNode* next = NULL;
    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
}
