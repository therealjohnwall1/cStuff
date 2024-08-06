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

    // temp will become a local pointer within function
    Node* temp = curr->head;
    Node* toInsert = nodeInit(key,value);

    if (temp == NULL) {
        // will not work since temp is a local pointer 
        /*temp = toInsert;*/
       curr->head = toInsert; 
       curr->bucketSize++;
       return 1;
    }
    printf("node already exists, going down chain\n");

    while(temp->next != NULL) {
        if (temp->value == value) {
           printf("found duplciate\n");
           dict->numEntries--;
           return -1;
        }
        temp = temp->next;
    }
    
    temp->next = toInsert;
    
    double loadFact =  (double)dict->numEntries/dict->tableSize; 

    if(loadFact >= 0.75) {
        //resize hashmap
    }
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

int expandDict(HashMap* dict) {
    printf("resizing current hashmap");
    // expand dict by 2
     HashMap* newDict = (HashMap*) malloc(sizeof(*newDict));    
    
     newDict->tableSize = 2*dict->tableSize;
     dict->map = (Bucket*) malloc(newDict->tableSize*sizeof(Bucket));
     newDict->numEntries = dict->numEntries;

     // go through each element and rehash and insert into new hashmap

}

void printHashMap(HashMap* dict) {
    for(int i=0; i< dict->tableSize;i++) {
        Bucket* buc = &(dict->map[i]);
        Node* curr = buc->head; 
        /*if(curr == NULL) {printf("curr is null\n");}*/
        printf("bucket %d \n", i);
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

  insert(dict, "imap", "poopoo");
  insert(dict, "first name", "last name");
  insert(dict, "first name", "last name");
  insert(dict, "googoogoo", "ooohhohhoooh");
  insert(dict, "google", "poopoo");
  insert(dict, "yahoo", "doodoo");
  insert(dict, "s", "dddd");
  insert(dict, "intel", "rip");
  
  
  /*printHashMap(dict);*/

  printf("retrieving now\n");

  char* imap = retrieve(dict,"imap");
  printf("imap->%s \n", imap);

  // free later
  /*free(dict);*/
  /*free(dict->map);*/
   /*free up the linked lists later*/
  return 0;
}

