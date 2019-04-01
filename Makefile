all: first
first: fileCompressor.c
	-gcc -g -lm -Wall -Werror -fsanitize=address fileCompressor.c -o fileCompressor
clean:
	rm -rf fileCompressor
