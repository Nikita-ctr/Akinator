#include "../lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Node *createNode(char *question) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->question = strdup(question);
    node->yes = NULL;
    node->no = NULL;
    return node;
}

void freeTree(Node *node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->yes);
    freeTree(node->no);
    free(node->question);
    free(node);
}

Node *buildTree(cJSON *obj) {
    if (!obj) {
        return NULL;
    }
    Node *node = createNode(cJSON_GetObjectItem(obj, "question")->valuestring);
    cJSON *yes = cJSON_GetObjectItem(obj, "yes");
    cJSON *no = cJSON_GetObjectItem(obj, "no");
    node->yes = buildTree(yes);
    node->no = buildTree(no);
    return node;
}

void printTree(Node *node, int depth) {
    if (node == NULL) {
        return;
    }
    printf("%*s- %s\n", depth * 2, "", node->question);
    printTree(node->yes, depth + 1);
    printTree(node->no, depth + 1);
}

cJSON *saveTreeHelper(Node *node) {
    if (!node) {
        return NULL;
    }

    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "question", node->question);

    if (node->yes != NULL) {
        cJSON_AddItemToObject(json, "yes", saveTreeHelper(node->yes));
    }

    if (node->no != NULL) {
        cJSON_AddItemToObject(json, "no", saveTreeHelper(node->no));
    }

    return json;
}

void saveTree(char *filename, Node *node) {
    cJSON *root = saveTreeHelper(node);

    char *json_string = cJSON_Print(root);
    cJSON_Delete(root);

    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fputc('[', file);
        fputs(json_string, file);
        fputc(']', file);
        fclose(file);
    }

    free(json_string);
}

void addNewAnswer(Node *node, char *newAnswer) {
    char question[50];
    sprintf(question, "%s?", newAnswer);
    Node *newNode = createNode(question);
    newNode->no = NULL;
    newNode->yes = NULL;
    node->no = newNode;
}