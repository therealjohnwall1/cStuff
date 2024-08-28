#include "linkedList.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Node *nodeInit(char *key, char *val) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = val;
  newNode->key = key;
  newNode->next = NULL;
  return newNode;
}
