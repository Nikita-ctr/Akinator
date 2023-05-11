#include "../lib.h"


void play(Node *current_node) {
    char answer[10];

    if (!current_node->yes && !current_node->no) {
        printf("I think it's %s!\nDid I guess right? (yes/no): ", current_node->question);
        scanf("%s", answer);
        if (strcmp(answer, "yes") == 0) {
            printf("Thank god! I win!\n");
            exit(EXIT_SUCCESS);
        } else {
            printf("Oh no, I was wrong :(\nWhat was it? ");
            char new_object[256], new_question[256];
            scanf(" %[^\n]", new_object);
            printf("What question can distinguish %s from %s? ", new_object, current_node->question);
            scanf(" %[^\n]", new_question);
            add_question(current_node, new_question, new_object);
            return;
        }
    }
    printf("%s (yes/no): ", current_node->question);
    scanf("%s", answer);
    if (strcmp(answer, "yes") == 0) {
        play(current_node->yes);
    } else {
        play(current_node->no);
    }
}

int main() {
    const char *file_path = "C:\\Users\\Nikita\\CLionProjects\\akinator\\db.txt";
    FILE *file = fopen(file_path, "r");
    Node *root = buildTree(file);
    printf("\nLet's play Akinator!\nAnswer the following questions with yes or no.\n");
    log_message("Game started");
    play(root);
    file = fopen(file_path, "wb");
    save_tree(file, root);

    fclose(file);
    freeTree(root);
    log_message("Game over: the program is shutting down");
    return 0;
}