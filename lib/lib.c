#include "../lib.h"

void log_message(char *message) {
    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    FILE *log_file = fopen("C:\\Users\\Nikita\\CLionProjects\\akinator\\log.txt", "a");
    fprintf(log_file, "[%s] %s\n", timestamp, message);
    fclose(log_file);
}

Node *createNode(char *question) {
    Node *new_node = malloc(sizeof(Node));
    new_node->question = question;
    new_node->yes = NULL;
    new_node->no = NULL;
    return new_node;
}

Node *buildTree(FILE *file) {
    char question[256];
    if (fgets(question, 256, file) == NULL) {
        log_message("buildTree(): reached end of file");
        return NULL;
    }
    if (strcmp(question, "*\n") == 0) {
        log_message("buildTree(): reached end of branch");
        return NULL;
    }
    question[strlen(question) - 1] = '\0';
    Node *new_node = createNode(strdup(question));
    new_node->yes = buildTree(file);
    new_node->no = buildTree(file);

    log_message("buildTree(): created node");
    return new_node;
}

void save_tree(FILE *file, Node *current_node) {
    if (current_node == NULL) {
        fprintf(file, "*\n");
        log_message("save_tree(): reached end of branch");
        return;
    }
    fprintf(file, "%s\n", current_node->question);
    save_tree(file, current_node->yes);
    save_tree(file, current_node->no);

    log_message("save_tree(): saved node");
}


void add_question(Node *current_node, char *new_question, char *new_object) {
    char *old_question = current_node->question;
    current_node->question = new_question;
    current_node->no = createNode(old_question);
    current_node->yes = createNode(new_object);

    log_message("add_question(): added new question and object");
}

void freeTree(Node *node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->yes);
    freeTree(node->no);
    free(node);

    log_message("freeTree(): freed node");
}


