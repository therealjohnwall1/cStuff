#include "linkedList.h"

struct Bucket{
    Node* head;
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

void destructor(HashMap* dict);
void expandDict(HashMap**dict);
