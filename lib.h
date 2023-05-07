#include <libxml/tree.h>

typedef struct Node Node;

struct Node {
    char *question;
    Node *yes;
    Node *no;
};

Node *buildTree(FILE *file);
void save_tree(FILE *file, Node *current_node);
void add_question(Node *current_node, char *new_question, char *new_object);
void freeTree(Node* node);
void log_message(char *message);

