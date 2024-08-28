
struct LinkedNode {
  char *value;
  char *key;
  struct LinkedNode *next;
};

typedef struct LinkedNode Node;

Node *nodeInit(char *key, char *val);
