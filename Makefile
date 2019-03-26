all: first
first: bst.c
	-gcc -g -Wall -Werror -fsanitize=address bst.c -o bst
clean:
	rm -rf bst
