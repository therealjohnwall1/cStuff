#include "linkedList.c"

struct Bucket{
    Node* head;
    Node* tail;
    int bucketSize;
};

typedef struct Bucket Bucket;

struct HashMap{
    int tableSize;
    int numEntries;
    
    //array of buckets
    Bucket *map;
};
typedef struct HashMap HashMap; 
