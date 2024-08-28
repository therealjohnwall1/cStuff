#pragma once
struct workNode {
  int fd;
  struct workNode *next;
};
typedef struct workNode workNode;

struct workQueue {
  workNode *head;
  workNode *tail;
};
typedef struct workQueue workQueue;

int append(int clientFD); // add to end

int pop(); // pop from begining

extern workQueue *q;
