#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "lexerf.h"
#include "parserf.h"
#include "codegeneratorf.h"

void traverse_tree(Node *node, int is_left, FILE *file) {
    if (node == NULL) {
        return;
    }
    if (strcmp(node->value, "EXIT") == 0) {
        fprintf(file, "\tmov rax, 60\n");
    }
    if (strcmp(node->value, "(") == 0) {

    }
    if (node->type == INT) {
        fprintf(file, "\tmov rdi, %s\n", node->value);

    }
    if (strcmp(node->value, ")") == 0) {

    }
    if (strcmp(node->value, ";") == 0) {
        fprintf(file, "\tsyscall\n");
    }



    if (is_left) {
        //
    } else {
        //
    }

    for (size_t i = 0; node->value[i] != '\0'; i++) {
        printf("%c", node->value[i]);
    }
    printf("\n");
    traverse_tree(node->left, 1, file);
    traverse_tree(node->right, 0, file);
}

int generate_code(Node *root) {
    FILE *file = fopen("generated.asm", "w");
    assert(file != NULL && "FILE COUND NOT BE OPENED");

    fprintf(file, "section .text\n");
    fprintf(file, "\tglobal Start\n\n");
    fprintf(file, "Start:\n");

    traverse_tree(root, 0, file);
    fclose(file);

    return 0;
}