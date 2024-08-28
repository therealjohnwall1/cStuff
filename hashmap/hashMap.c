#include "hashMap.h"
#include "hashFn.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int insert(HashMap **dict, char *key, char *value) {
  (*dict)->numEntries++;
  int hash = hashFn(key, (*dict)->tableSize);
  Bucket *curr = &((*dict)->map[hash]);

  Node *temp = curr->head;
  Node *toInsert = nodeInit(key, value);

  if (temp == NULL) {
    curr->head = toInsert;
    curr->bucketSize++;
    return 1;
  }

  while (temp->next != NULL) {
    if (temp->value == value) {
      (*dict)->numEntries--;
      return -1;
    }
    temp = temp->next;
  }

  temp->next = toInsert;

  double loadFact = (double)(*dict)->numEntries / (*dict)->tableSize;

  if (loadFact >= 0.75) {
    printf("loadfactor = %lf, resizing dict\n", loadFact);
    expandDict(dict);
  }
  return 0;
}

char *retrieve(HashMap *dict, char *key) {
  int hash = hashFn(key, dict->tableSize);
  Bucket *curr = &(dict->map[hash]);
  Node *temp = curr->head;

  while (temp != NULL) {
    if (temp->key == key) {
      return temp->value;
    }
  }
  printf("No value found.");
  return NULL;
}

void expandDict(HashMap **dict) {
  printf("resizing current hashmap\n");

  // Allocate memory for the new HashMap
  HashMap *newDict = (HashMap *)malloc(sizeof(HashMap));
  int oldSize = (*dict)->tableSize;
  printf("old size %d\n", oldSize);

  // Double the table size
  newDict->tableSize = 2 * oldSize;
  newDict->numEntries = 0;
  newDict->map = (Bucket *)malloc(newDict->tableSize * sizeof(Bucket));

  // Initialize new buckets
  for (int i = 0; i < newDict->tableSize; i++) {
    newDict->map[i].head = NULL;
  }

  // Rehash and insert elements into the new hashmap
  for (int i = 0; i < oldSize; i++) {
    Node *startNode = (*dict)->map[i].head;
    while (startNode != NULL) {
      insert(&newDict, startNode->key, startNode->value);
      startNode = startNode->next;
    }
  }
  destructor(*dict);
  *dict = newDict;
  printf("new dict size %d\n", (*dict)->tableSize);
}

void printHashMap(HashMap *dict) {
  printf("printing hashmap\n");

  for (int i = 0; i < dict->tableSize; i++) {
    Bucket *buc = &(dict->map[i]);
    Node *curr = buc->head;
    /*if(curr == NULL) {printf("curr is null\n");}*/
    printf("bucket %d \n", i);
    while (curr != NULL) {
      printf("key:%s, value:%s\n", curr->key, curr->value);
      curr = curr->next;
    }
  }
  double loadFact = (double)dict->numEntries / dict->tableSize;
  printf("num entries: %d, tableSize: %d \n", dict->numEntries,
         dict->tableSize);
  printf("load factor %lf\n", loadFact);
}

HashMap *constructor() {
  HashMap *dict = (HashMap *)malloc(sizeof(*dict));
  // init size of 10
  dict->tableSize = 10;
  dict->map = (Bucket *)malloc(10 * sizeof(Bucket));
  dict->numEntries = 0;
  for (int i = 0; i < dict->tableSize; i++) {
    dict->map[i].head = NULL;
    dict->map[i].bucketSize = 0;
  }
  return dict;
}

void destructor(HashMap *dict) {
  for (int i = 0; i < dict->tableSize; i++) {
    Bucket *buc = &(dict->map[i]);
    Node *curr = buc->head;
    Node *prev;

    printf("bucket %d \n", i);
    while (curr != NULL) {
      prev = curr;
      curr = curr->next;
      free(prev);
    }
  }
  free(dict->map);
  free(dict);
}

int main(void) {
  HashMap *dict = constructor();
  insert(&dict, "imap", "poopoo");
  insert(&dict, "first name", "last name");
  insert(&dict, "first name", "last name");
  insert(&dict, "googoogoo", "ooohhohhoooh");
  insert(&dict, "google", "poopoo");
  insert(&dict, "yahoo", "doodoo");
  insert(&dict, "s", "dddd");
  insert(&dict, "intel", "rip");

  printHashMap(dict);
  destructor(dict);
  return 0;
}
