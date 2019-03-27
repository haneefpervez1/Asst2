all: first
first: fileCompressor.c
	-gcc -g -Wall -Werror -fsanitize=address fileCompressor.c bst.c -o fileCompressor
clean:
	rm -rf fileCompressor
