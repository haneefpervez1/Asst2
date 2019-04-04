int main (int argc, char ** argv)
{
 if(argc>5)
 {
  printf("Error. Too mnay input argumetns");
  return;
 }
 int fd;
 char* flag2;
 char* flag = argv[1];
 char* file = argv[2];
 char* codebook = argv[3];
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
 	  struct dirent *de;
	  DIR * dr = opendir(path);
	  de = readdir(dr);
	  if(de->d_type!=DT_REG)
	  {
	  	printf("Error. Only compress regular files");
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
 	  fd = open(file, O_RDONLY | O_CREAT);
    	  decompress(file, fd, codebook);
    	  close(fd);
 	  break;
 	 case('R'):
 	  flag2 = argv[2];
 	  file = argv[3];
 	  if(flag2==NULL)
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
