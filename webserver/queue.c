#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

workQueue* q; 

int append(int clientFD) {
    workNode* toInsert = (workNode*) malloc(sizeof(workNode));
    if (toInsert == NULL) {
        perror("malloc failed");
        return -1;
    }
    toInsert->fd = clientFD;
    toInsert->next = NULL;

    if ((q->head == NULL) && (q->tail == NULL)) {
        q->head = toInsert;
        q->tail = toInsert;
    } else {
        q->tail->next = toInsert;
        q->tail = toInsert;
    }
    printf("appendced %d\n", clientFD);
    return 0;
} 

int pop() {
    if (q->head == NULL) {
        printf("end of list\n");
        return -1; 
    }

    int res = q->head->fd;

    workNode* toDel = q->head;
    if(q->head->next != NULL){
        printf("head = %d, next = %d\n", q->head->fd, q->head->next->fd);
    }else{
        printf("head = %d\n", q->head->fd);
    }
    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL; 
    }
    free(toDel);

    return res;
}

// int main() {
//     q = (workQueue*) malloc(sizeof(workQueue));
//     // test appending to the queue
//     append(1);
//     append(2);
//     append(3);
//     append(4);

//     // test popping from the queue
//     printf("popped: %d\n", pop()); // should print 1
//     printf("popped: %d\n", pop()); // should print 2
//     printf("popped: %d\n", pop()); // should print 3
//     printf("popped: %d\n", pop()); // should print -1 (queue is empty)

//     return 0;
// }
