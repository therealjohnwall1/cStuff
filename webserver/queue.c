#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int append(workQueue* q, int clientFD) {
    workNode* toInsert = (workNode*) malloc(sizeof(workNode*));
    toInsert->fd = clientFD;
    toInsert->next = NULL;

    if ((q->head == NULL) && (q->tail == NULL)) {
        q->head = toInsert;
        q->tail = toInsert;
    }
    else {
        q->tail->next = toInsert;
    }

    return 0;
} 

int* pop(workQueue* q) {
    if (q->head == NULL) {
        return NULL;
    }
    int res = q->head->fd;

    workNode* toDel = q->head;
    q->head = q->head->next;
    free(toDel);

    return &res;
}

