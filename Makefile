CC=gcc
AR=ar
FLAGS= -Wall -g
all: frequency 

frequency: main_trie.o mytrie     
	$(CC) $(FLAGS) -o frequency main_trie.o mytrie 
mytrie: trie.o
	$(AR) -rcs mytrie trie.o
trie.o: trie.c trie.h
	$(CC) $(FLAGS) -c trie.c
main_trie.o: main_trie.c trie.h 
	$(CC) $(FLAGS) -c main_trie.c

.PHONY: clean all

clean:
	rm frequency mytrie *.o