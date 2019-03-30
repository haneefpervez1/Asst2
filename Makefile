all: first
first: huffman.c
	-gcc -g -lm -Wall -Werror -fsanitize=address huffman.c -o huffman
clean:
	rm -rf huffman
