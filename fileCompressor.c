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
	/*
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
 mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
 char* buff[1];
 int CB = creat("HuffmanCodeBook", mode);
 int x = read(fd, tok, 1);
 	while(x!=0)
 	{
 	 
 	}

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
	
	DIR *dr = opendir(".");
	
	if (dr == NULL) {
		printf("error\n");
	}
	while ((de = readdir(dr)) != NULL) {
		printf("%s\n", de->d_name);
	}
	closedir(dr);
}
int main (int argc, char ** argv)
{
 int fd;
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
 	  close(fd);
 	 // printf("%d", fd);
 	  break;
 	 case('c'):
 	  fd = open(file, O_RDONLY | O_CREAT); 
 	  compress(file, fd, codebook);
 	  break;
 	 case('d'):
 	  decompress(file, fd, codebook);
 	  break;
 	 case('R'):
 	  
 	 break;
 	}
  return 0;
}
