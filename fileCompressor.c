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
 char* flag = argv[1];
 char* file = argv[2];
 char* codebook = argv[3];
 printf("%s %s %s", flag, file, codebook);
 	switch(flag[1])
 	{
 	 case('b'):
 	  
 	  break;
 	 case('c'):
 	  break;
 	 case('d'):
 	  break;
 	 case('R'):
 	 break;
 	}
  return 0;
}
