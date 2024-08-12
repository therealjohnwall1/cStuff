#pragma once
struct workNode {
    int fd;
    struct workNode* next;
};
typedef struct workNode workNode;

struct workQueue {
    workNode* head;
    workNode* tail;
}; 
typedef struct workQueue workQueue;

int append(workQueue* q,int clientFD); // add to end

int pop(workQueue* q); // pop from begining 

