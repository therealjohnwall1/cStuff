CC = gcc
CFLAGS = -g -Wall -Wextra -Wpedantic --std=c17

#target
hashmap: hashmap.o hashFn.o linkedList.o 
	$(CC) $(CFLAGS) $^ -o $@

#object file
hashmap.o: hashMap.c hashMap.h
	$(CC) $(CFLAGS) -c $< -o $@

hashFn.o: hashFn.c hashFn.h
	$(CC) $(CFLAGS) -c $< -o $@

linkedList.o: linkedList.c linkedList.h
	$(CC) $(CFLAGS) -c $< -o $@

#cleanup
clean:
	rm -f *.o hashmap

.PHONY: clean

