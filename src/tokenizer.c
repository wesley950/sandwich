//
// Created by wesley on 08/05/22.
//

#include "tokenizer.h"

struct token_list_t* tokenizer_tokenize(const char* input) {
    struct token_list_t* token_list = (struct token_list_t*) malloc(sizeof(struct token_list_t));

    token_list->length = 0;
    token_list->capacity = 1;
    token_list->tokens = (struct token_t*) malloc(sizeof(struct token_t) * token_list->capacity);

    int32_t current_char_idx = 0;
    char current_char = input[current_char_idx];

    while (1) {
        if (current_char >= '0' && current_char <= '9') {
            struct token_t token;
            token.type = TK_INTEGER_LITERAL;
            token.value = tokenizer_scan_integer_literal(input, &current_char_idx);
            token_list_add(token_list, token);
        }
        else if (current_char == '+') {
            struct token_t token;
            token.type = TK_ADD;
            token.value = 0;
            token_list_add(token_list, token);
            current_char_idx++;
        }
        else if (current_char == '-') {
            struct token_t token;
            token.type = TK_SUBTRACT;
            token.value = 0;
            token_list_add(token_list, token);
            current_char_idx++;
        }
        else if (current_char == '*') {
            struct token_t token;
            token.type = TK_MULTIPLY;
            token.value = 0;
            token_list_add(token_list, token);
            current_char_idx++;
        }
        else if (current_char == '/') {
            struct token_t token;
            token.type = TK_DIVIDE;
            token.value = 0;
            token_list_add(token_list, token);
            current_char_idx++;
        }
        else if (current_char == '\n' || current_char == ' ') {
            current_char_idx++;
        }
        else if (current_char == '\0') {
            break;
        }
        current_char = input[current_char_idx];
    }

    return token_list;
}

int32_t tokenizer_scan_integer_literal(const char* input, int32_t* starting_idx) {
    int32_t value = 0;
    int32_t idx = *starting_idx;
    char current_char = input[idx];
    int32_t digit = 0;

    while (1) {
        switch (current_char) {
            case '0':
                digit = 0;
                break;

            case '1':
                digit = 1;
                break;

            case '2':
                digit = 2;
                break;

            case '3':
                digit = 3;
                break;

            case '4':
                digit = 4;
                break;

            case '5':
                digit = 5;
                break;

            case '6':
                digit = 6;
                break;

            case '7':
                digit = 7;
                break;

            case '8':
                digit = 8;
                break;

            case '9':
                digit = 9;
                break;

            default:
                // TODO: throw error message and die
                digit = -1;
                break;
        }

        if (digit != -1) {
            value *= 10;
            value += digit;
        }
        else {
            break;
        }

        idx++;
        current_char = input[idx];
    }

    *starting_idx = idx;
    return value;
}

const char* tokenizer_type_to_string(enum token_type_e type) {
    switch (type) {
        case TK_INTEGER_LITERAL:
            return "INTEGER LITERAL";

        case TK_ADD:
            return "ADD";

        case TK_SUBTRACT:
            return "SUBTRACT";

        case TK_MULTIPLY:
            return "MULTIPLY";

        case TK_DIVIDE:
            return "DIVIDE";

        default:
            break;
    }

    return "INVALID";
}

void tokenizer_free_token_list(struct token_list_t* token_list) {
    if (token_list->tokens != NULL)
        free(token_list->tokens);
    free(token_list);
}

void token_list_add(struct token_list_t* token_list, struct token_t token) {
    if (token_list->length == token_list->capacity) {
        int32_t new_capacity = token_list->capacity * 2;
        token_list->tokens = (struct token_t*) realloc(token_list->tokens, sizeof(struct token_t) * new_capacity);
        token_list->capacity = new_capacity;
    }

    token_list->tokens[token_list->length] = token;
    token_list->length++;
}
