//
// Created by wesley on 08/05/22.
//

#pragma once

#include <stdint.h>
#include <stdlib.h>

enum token_type_e {
    TK_INVALID,
    TK_ADD, TK_SUBTRACT, TK_MULTIPLY, TK_DIVIDE,
    TK_INTEGER_LITERAL
};

struct token_t {
    enum token_type_e type;
    int32_t value;
};

struct token_list_t {
    struct token_t* tokens;
    int32_t length;
    int32_t capacity;
};

struct token_list_t* tokenizer_tokenize(const char* input);
const char* tokenizer_type_to_string(enum token_type_e type);
int32_t tokenizer_scan_integer_literal(const char* input, int32_t* starting_idx);
void tokenizer_free_token_list(struct token_list_t* token_list);

void token_list_add(struct token_list_t* token_list, struct token_t token);
