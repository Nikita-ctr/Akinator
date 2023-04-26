#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "../lib.h"


void play(Node *node, char *file_contents) {
    char answer[10];
    if (node->no == NULL) {
        printf("Is it %s\n", node->question);
        scanf("%s", answer);
        if (strcmp(answer, "yes") == 0) {
            printf("Great! I guessed it!\n");
        } else {
            printf("I give up. What were you thinking of?\n");
            scanf("%s", answer);
            addNewAnswer(node, answer);

        }
    } else {
        printf("%s\n", node->question);
        scanf("%s", answer);
        if (strcmp(answer, "yes") == 0) {
            play(node->yes, file_contents);
        } else {
            play(node->no, file_contents);
        }
    }
}


int main() {

    FILE *fp = fopen("db.json", "rb");
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *file_contents = malloc(file_size + 1);
    fread(file_contents, file_size, 1, fp);
    fclose(fp);
    file_contents[file_size] = '\0';

    cJSON *root = cJSON_Parse(file_contents);
    if (!root) {
        printf("Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        return 1;
    }
    Node *tree = buildTree(root->child);

    printf("\nLet's play Akinator!\n");
    printf("Answer the following questions with yes or no.\n");

    play(tree, file_contents);

    saveTree("db.json", tree);

    cJSON_Delete(root);
    free(file_contents);
    freeTree(tree);
    return 0;

}