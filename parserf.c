#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexerf.h"
#include "parserf.h"

void print_tree(Node *node, int indent, char *identifier) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < indent; i++) {
        printf(" ");
    }
    printf("%s -> ", identifier);
    for(size_t i = 0; node->value[i] != '\0'; i++) {
        printf("%c", node->value[i]);
    }
    printf("\n");
    print_tree(node->left, indent + 1, "left");
    print_tree(node->right, indent + 1, "right");
}

Node *init_node(Node *node, char *value, TokenType type) {
    node = malloc(sizeof(Node));
    node->value = malloc(sizeof(char) * 2);
    node->value = value;
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void print_error(char *error_type) {
    printf("ERROR: %s\n", error_type);
    exit(1);
}

Node *parser(Token *tokens) {
    Token *current_token = &tokens[0];
    Node *root = malloc(sizeof(Node));
    root = init_node(root, "PROGRAM", BEGINNING);

    Node *current = root;

    while (current_token->type != END_OF_TOKENS) {
        if (current == NULL) {
            break;
        }
        if (current == root) {
            //;
        }

        switch (current_token->type) {
            case KEYWORD:
                if (strcmp(current_token->value, "EXIT") == 0) {
                    Node *exit_node = malloc(sizeof(Node));
                    exit_node = init_node(exit_node, current_token->value, KEYWORD);
                    root->right = exit_node;
                    current = exit_node;
                    current_token++;
                    if (strcmp(current_token->value, "(") == 0 && current_token->type == SEPARATOR) {
                        Node *open_paren_node = malloc(sizeof(Node));
                        open_paren_node = init_node(open_paren_node, current_token->value, SEPARATOR);
                        current->left = open_paren_node;
                        current_token++;
                        if (current_token->type == INT) {
                            Node *expr_node = malloc(sizeof(Node));
                            expr_node = init_node(expr_node, current_token->value, INT);
                            current->left->left = expr_node;
                            current_token++;
                            if (strcmp(current_token->value, ")") == 0 && current_token->type == SEPARATOR) {
                                Node *close_paren_node = malloc(sizeof(Node));
                                close_paren_node = init_node(close_paren_node, current_token->value, SEPARATOR);
                                current->left->right = close_paren_node;
                                current_token++; 
                                if (strcmp(current_token->value, ";") == 0 && current_token->type == SEPARATOR) {
                                    Node *semicolon_node = malloc(sizeof(Node));
                                    semicolon_node = init_node(semicolon_node, current_token->value, SEPARATOR);
                                    current->right = semicolon_node;
                                    break;
                                } else {
                                    print_error("Invalid Syntax on SEMI\n");
                                }
                            } else {
                                print_error("Invalid Syntax on CLOSE\n");
                            }
                        } else {
                            print_error("Invalid Syntax on INT\n");
                        }
                    } else {
                        print_error("Invalid Syntax on OPEN\n");
                    }
                }
                break;
            case SEPARATOR:
                //;
                break;
            case INT:
                printf("INTEGER\n");
                break;
            case BEGINNING:
                //;
                break; 
            case END_OF_TOKENS:
                //;
                break;
        }
        current_token++;
    }
    print_tree(root, 0, "root");
    return root;
}