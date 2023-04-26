#include <libxml/tree.h>
#include "ext/cJSON.h"

typedef struct Node Node;

struct Node {
    char* question;
    Node* yes;
    Node* no;
};

Node *createNode(char *question);
void freeTree(Node *node);
Node *buildTree(cJSON *obj);
void printTree(Node *node, int depth);
cJSON *saveTreeHelper(Node *node);
void saveTree(char *filename, Node *node);
void addNewAnswer(Node *node, char *newAnswer);

