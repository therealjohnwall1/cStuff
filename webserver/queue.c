#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int append(workQueue* q, int clientFD) {
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

    return 0;
} 

int pop(workQueue* q) {
    if (q->head == NULL) {
        printf("end of list\n");
        return -1; 
    }
    int res = q->head->fd;

    workNode* toDel = q->head;
    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL; 
    }
    free(toDel);

    return res;
}

// int main() {
//     workQueue q = {NULL, NULL};

//     // Test appending to the queue
//     append(&q, 1);
//     append(&q, 2);
//     append(&q, 3);

//     // Test popping from the queue
//     printf("Popped: %d\n", pop(&q)); // Should print 1
//     printf("Popped: %d\n", pop(&q)); // Should print 2
//     printf("Popped: %d\n", pop(&q)); // Should print 3
//     printf("Popped: %d\n", pop(&q)); // Should print -1 (queue is empty)

//     return 0;
// }
