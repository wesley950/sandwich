//
// Created by wesley on 09/05/22.
//

#include "parser.h"

static struct token_list_t* current_token_list = NULL;
static int32_t current_token_idx = 0;

struct ast_node_t* parser_build_ast(struct token_list_t* token_list) {
    if (token_list->length == 0) {
        // TODO: error out
        return NULL;
    }

    current_token_list = token_list;
    current_token_idx = 0;

    struct ast_node_t* primary = parser_expression();
}

struct ast_node_t* parser_expression() {
    struct ast_node_t* left, *right, *expression;
    enum ast_node_operation_e operation;

    left = parser_primary();

    if (current_token_list->length == current_token_idx)
        return left;

    struct token_t* next_token = &current_token_list->tokens[current_token_idx];

    operation = parser_type_from_tokenizer(next_token->type);
    current_token_idx++;
    right = parser_expression();
    expression = parser_make_operation(operation, left, right);

    return expression;
}

struct ast_node_t* parser_primary() {
    struct token_t* current_token = &current_token_list->tokens[current_token_idx];

    switch (current_token->type) {
        case TK_INTEGER_LITERAL: {
            struct ast_node_t* node = parser_make_integer_node(current_token->value);
            current_token_idx++;
            return node;
        }

        default:
            // TODO: print out error
            exit(-1);
    }
}

struct ast_node_t* parser_make_integer_node(int32_t value) {
    struct ast_node_t* node = (struct ast_node_t*) malloc(sizeof(struct ast_node_t));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->operation = OP_ADD;
    return node;
}

struct ast_node_t* parser_make_operation(enum ast_node_operation_e operation, struct ast_node_t* left, struct ast_node_t* right) {
    struct ast_node_t* node = (struct ast_node_t*) malloc(sizeof(struct ast_node_t));
    node->value = 0;
    node->left = left;
    node->right = right;
    node->operation = operation;
    return node;
}

enum ast_node_operation_e parser_type_from_tokenizer(enum token_type_e type) {
    switch (type) {
        case TK_INTEGER_LITERAL:
        case TK_ADD:
            return OP_ADD;

        case TK_SUBTRACT:
            return OP_SUBTRACT;

        case TK_MULTIPLY:
            return OP_MULTIPLY;

        case TK_DIVIDE:
            return OP_DIVIDE;

        default:
            return OP_INVALID;
    }
}

int32_t parser_evaluate(struct ast_node_t* ast_root) {
    int32_t result = 0;
    int32_t left_result = 0, right_result = 0;

    if (ast_root == NULL)
        return 0;

    if (ast_root->left != NULL)
        left_result = parser_evaluate(ast_root->left);
    if (ast_root->right != NULL)
        right_result = parser_evaluate(ast_root->right);

    switch (ast_root->operation) {
        case OP_ADD:
            result = left_result + right_result + ast_root->value;
            break;

        case OP_SUBTRACT:
            result = left_result - right_result;
            break;

        case OP_MULTIPLY:
            result = left_result * right_result;
            break;

        case OP_DIVIDE:
            result = left_result / right_result;
            break;

        default:
            // TODO: print out about the INVALID operator
            exit(-1);
    }

    return result;
}

void parser_free_ast(struct ast_node_t* ast_root) {
    if (ast_root->left != NULL)
        parser_free_ast(ast_root->left);
    if (ast_root->right != NULL)
        parser_free_ast(ast_root->right);

    free(ast_root);
}
