//
// Created by wesley on 09/05/22.
//

#pragma once

#include <stdint.h>

#include "tokenizer.h"

enum ast_node_operation_e {
    OP_INVALID,
    OP_ADD, OP_SUBTRACT, OP_MULTIPLY, OP_DIVIDE
};

struct ast_node_t {
    struct ast_node_t* left;
    struct ast_node_t* right;
    int32_t value;
    enum ast_node_operation_e operation;
};

struct ast_node_t* parser_build_ast(struct token_list_t* token_list);
struct ast_node_t* parser_expression();
struct ast_node_t* parser_primary();
struct ast_node_t* parser_make_integer_node(int32_t value);
struct ast_node_t* parser_make_operation(enum ast_node_operation_e operation, struct ast_node_t* left, struct ast_node_t* right);
enum ast_node_operation_e parser_type_from_tokenizer(enum token_type_e type);
int32_t parser_evaluate(struct ast_node_t* ast_root);
void parser_free_ast(struct ast_node_t* ast_root);
