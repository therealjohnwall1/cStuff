CC = g++

CFLAGS = -g -Wall -Wextra -Wpedantic 

# Target (Huffman)
huffman: huffman.o nodes.o
	$(CC) $(CFLAGS) $^ -o $@

# Object 
huffman.o: huffman.cpp huffman.h
	$(CC) $(CFLAGS) -c $< -o $@

# Object
nodes.o: nodes.cpp nodes.h
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f *.o huffman 

.PHONY: clean

