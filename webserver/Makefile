CC = gcc
CFLAGS = -g -Wall -Wextra -Wpedantic --std=c17

# Target (Client)
client: client.o
	$(CC) $(CFLAGS) $^ -o $@

# Object
client.o: client.c client.h
	$(CC) $(CFLAGS) -c $< -o $@

# clean
clean:
	rm -f *.o client

.PHONY: clean
