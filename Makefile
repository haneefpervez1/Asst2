all: first
first: huffman.c fileCompressor.c
	-gcc -g -lm -Wall -Werror -fsanitize=address huffman.c fileCompressor.c -o huffman
clean:
	rm -rf huffman
