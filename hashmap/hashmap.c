#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "hashmap.h"
#include "hashFn.c"

int insert(HashMap* dict,char* key, char* value) {
    dict->numEntries++;
    int hash = hashFn(key,dict->tableSize);
    Bucket* curr = &(dict->map[hash]);
    // head will become a local pointer within function
    Node* temp = curr->head;
    Node* toInsert = nodeInit(key,value);
    if (temp == NULL) {
       curr->head = toInsert; 
       curr->bucketSize++;
       return 1;
    }

    while(temp != NULL) {
        if (temp->value == value) {
           dict->numEntries--;
           return -1;
        }
        temp = temp->next;
    }
    temp->next = toInsert;
    return 0;
}

char* retrieve(HashMap* dict, char* key) {
    int hash = hashFn(key, dict->tableSize);
    Bucket* curr = &(dict->map[hash]);
    Node* temp = curr->head;

    while(temp != NULL) {
        if(temp->key== key) {
            return temp->value;
        }
    }
    printf("No value found.");
    return NULL;
}

void printHashMap(HashMap* dict) {
    for(int i=0; i< dict->tableSize;i++) {
        Bucket* buc = &(dict->map[i]);
        printf("Bucket %d\n", buc->bucketSize);
        Node* curr = buc->head; 
        if(curr == NULL) {printf("curr is null\n");}
        while(curr != NULL) {
            printf("key:%s, value:%s\n", curr->key,curr->value); 
            curr = curr->next;
        } 
    }

    double loadFact =  (double)dict->numEntries/dict->tableSize; 
    printf("load factor %lf", loadFact);
}

int main(void) {
  HashMap* dict = (HashMap*) malloc(sizeof(*dict));    
  // init size of 10
  dict->tableSize = 10;
  dict->map = (Bucket*) malloc(10*sizeof(Bucket));
  dict->numEntries = 0;

  int first = insert(dict, "imap", "poopoo");
  printf("%d",first);
  insert(dict, "first name", "last name");
  insert(dict, "first name", "last name");
  insert(dict, "googoogoo", "ooohhohhoooh");
  
  printHashMap(dict);
  return 0;
}

