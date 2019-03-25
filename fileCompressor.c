#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main (int argc, char** argv) {
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
	return 0;
}

