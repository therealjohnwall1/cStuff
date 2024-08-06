#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct LinkedNode {
    char* value;
    char* key; 
    struct LinkedNode* next;
};

typedef struct LinkedNode Node;

Node* nodeInit(char* key, char* val) {
   Node *newNode = (Node*)malloc(sizeof(Node)); 
   newNode->value = val;
   newNode->key = key;
   return newNode;
}

