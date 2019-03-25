all: first
first: fileCompressor.c
	-gcc -g -Wall -Werror -fsanitize=address fileCompressor.c -o fileCompressor
clean:
	rm -rf fileCompressor
